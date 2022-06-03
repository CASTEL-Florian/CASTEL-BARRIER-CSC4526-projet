#include "Monster.h"
#include <cmath>

Monster::Monster(Player* player, RoomGenerator* roomGenerator, sf::Texture* texture) : 
	player(player), roomGenerator(roomGenerator), texture(texture)
{
	std::pair<int, int> farthestRoomPos = roomGenerator->getFarthestRoomPos();
	
	x = (farthestRoomPos.first + 0.5f) * roomWidth* tileWidth;
	y = (farthestRoomPos.second + 0.5f) * roomHeight * tileHeight;
	explore();
}

void Monster::display(sf::RenderWindow& window) const {
	/*sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(2, 2));
	rect.setOrigin(rect.getSize() / 2.f);
	rect.setRotation(angle);
	rect.setFillColor(sf::Color::Red);
	rect.setPosition(x, y);
	window.draw(rect);*/
	sf::Sprite sprite;
	sprite.setTexture(*texture);
	sprite.setTextureRect(sf::IntRect(rectOffsetX, rectOffsetY, 256, 128));
	sprite.setScale(sf::Vector2f(0.2f, 0.2f));
	sf::FloatRect bounds = sprite.getLocalBounds();
	float wi = bounds.width;
	float hi = bounds.height;
	sprite.setOrigin(sf::Vector2f(wi, hi) / 2.f);
	sprite.setPosition(sf::Vector2f(x, y));
	sprite.setRotation(angle + 180);
	if (action == State::Attack) sprite.setScale(sf::Vector2f(-0.2f, 0.2f));
	window.draw(sprite);
}

void Monster::animSprite() {
	if (action == State::Attack) {
		rectOffsetY = 128;
		if (lastState == false) rectOffsetX = 0;
		if (animTimer.getElapsedTime().asSeconds() >= attackDuration / 10) {
			rectOffsetX += 256;
			if (rectOffsetX >= 2304) {
				rectOffsetX = 0;
			}
			animTimer.restart();
		}
		lastState = true;
	}
	else {
		rectOffsetY = 0;
		if (lastState == true) rectOffsetX = 0;
		if (animTimer.getElapsedTime().asMilliseconds() >= 100) {
			rectOffsetX += 256;
			if (rectOffsetX >= 1792) {
				rectOffsetX = 0;
			}
			animTimer.restart();
		}
		lastState = false;
	}
}

void Monster::update() {
	if (action == State::Flee) {
		actionTime -= 1 / 60.f;
		if (actionTime <= 0) {
			sleep(5);
		}
	}
	if (action == State::Explore) {
		rotateToward(targetX, targetY);
		if (std::abs(x - targetX) < tileWidth && std::abs(y - targetY) < tileHeight) {
			sleep(1);
		}
		if (distanceFromPlayer() <= playerDetectRange) {
			follow();
		}
	}
	if (chaseTime <= 0 && action == State::Follow) {
		flee();
	}
	if (action == State::Sleep) {
		actionTime -= 1 / 60.f;
		if (distanceFromPlayer() <= playerDetectRange) {
			follow();
		}
		if (actionTime <= 0) {
			explore();
		}
		return;
	}
	
	if (action == State::Follow && distanceFromPlayer() <= attackRange) {
		prepareAttack();
	}
	if (action == State::PrepareAttack) {
		actionTime -= 1 / 60.f;
		chaseTime -= 1 / 60.f;
		if (actionTime < 0) {
			dash();
		}

	}
	if (action == State::Attack) {
		actionTime -= 1 / 60.f;
		chaseTime -= 1 / 60.f;
		if (actionTime < 0) {
			follow();
		}
	}
	if (action == State::Follow) {
		chaseTime -= 1 / 60.f;
		rotateToward(player->get_x(), player->get_y());
	}
	moveForward();
	animSprite();
}

void Monster::rotateToward(float x1, float y1)
{
	sf::Vector2f dir(x1 - x, y1 - y);
	if (dir.x == 0) {
		if (dir.y >= 0)
			angle = 90;
		else
			angle = -90;
		return;
	}
	if (dir.x > 0) {
		angle = std::atan(dir.y / dir.x) * (180 / b2_pi);
	}
	else
	{
		angle = 180 + std::atan(dir.y / dir.x) * (180 / b2_pi);
	}
}

void Monster::moveForward()
{
	x += std::cos(angle * b2_pi / 180) * speed / 60;
	y += std::sin(angle * b2_pi / 180) * speed / 60;
}

float Monster::distanceFromPlayer() const
{
	sf::Vector2f dir(player->get_x() - x, player->get_y() - y);
	return std::sqrt(dir.x*dir.x + dir.y * dir.y);
}

std::pair<float, float> Monster::getRandomMapPosition()
{
	auto roomPos = roomGenerator->getRandomRoomPos();
	std::pair<float, float> pos(roomPos.first * roomWidth* tileWidth, roomPos.second * roomHeight * tileHeight);
	pos.first += (random_1_to_n(roomWidth) - 1) * tileWidth;
	pos.second += (random_1_to_n(roomHeight) - 1) * tileHeight;
	return pos;
}

void Monster::explore()
{
	//std::cout << "Exploring\n";
	action = State::Explore;
	auto pos = getRandomMapPosition();
	targetX = pos.first;
	targetY = pos.second;
	speed = followSpeed;
}

void Monster::sleep(float duration)
{
	//std::cout << "Sleeping\n";
	action = State::Sleep;
	chaseTime = 10;
	actionTime = duration;
}

void Monster::dash()
{
	//std::cout << "Dashing\n";
	action = State::Attack;
	speed = dashSpeed;
	actionTime = attackDuration;
}

void Monster::follow()
{
	//std::cout << "Following\n";
	action = State::Follow;
	speed = followSpeed;
}

void Monster::prepareAttack()
{
	//std::cout << "Preparing attack\n";
	action = State::PrepareAttack;
	actionTime = prepareAttackDuration;
	speed = 0;
}

void Monster::flee()
{
	//std::cout << "Fleeing\n";
	action = State::Flee;
	actionTime = 5;
	speed = followSpeed/2;
	rotateToward(2 * x - player->get_x(), 2 * y - player->get_y());
}
