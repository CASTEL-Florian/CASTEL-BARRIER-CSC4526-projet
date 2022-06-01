#include "Monster.h"
#include <cmath>

Monster::Monster(Player* player, std::vector<std::unique_ptr<Room>> const& rooms) : player(player)
{
	float farthestRoomDistance = 0;
	std::pair<int, int> farthestRoomPos (0,0);
	for (auto const& room : rooms) {
		int roomX = room->get_x();
		int roomY = room->get_y();
		roomPositions.push_back(std::pair<int,int>(roomX, roomY));
		float roomDistance = roomX * roomX + roomY * roomY;
		if (roomDistance > farthestRoomDistance) {
			farthestRoomDistance = roomDistance;
			farthestRoomPos = std::pair<int, int>(roomX, roomY);
		}
	}
	x = (farthestRoomPos.first + 0.5f) * roomWidth* tileWidth;
	y = (farthestRoomPos.second + 0.5f) * roomHeight * tileHeight;
	explore();
}

void Monster::display(sf::RenderWindow& window) const {
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(2, 2));
	rect.setOrigin(rect.getSize() / 2.f);
	rect.setRotation(angle);
	rect.setFillColor(sf::Color::Red);
	rect.setPosition(x, y);
	window.draw(rect);
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
	chaseTime -= 1 / 60.f;
	
	if (action == State::Follow && distanceFromPlayer() <= attackRange) {
		prepareAttack();
	}
	if (action == State::PrepareAttack) {
		actionTime -= 1 / 60.f;
		if (actionTime < 0) {
			dash();
		}

	}
	if (action == State::Attack) {
		actionTime -= 1 / 60.f;
		if (actionTime < 0) {
			follow();
		}
	}
	if (action == State::Follow) {
		rotateToward(player->get_x(), player->get_y());
	}
	moveForward();
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
	auto& roomPos = roomPositions[random_1_to_n(roomPositions.size()) - 1];
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
