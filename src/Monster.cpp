#include "Monster.h"
#include <cmath>

Monster::Monster(Player* player) : player(player)
{
	x = player->get_x();
	y = player->get_y();
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
	if (action == State::Follow && distanceFromPlayer() <= attackRange) {
		action = State::PrepareAttack;
		time = prepareAttackDuration;
		speed = 0;
	}
	if (action == State::PrepareAttack) {
		time -= 1 / 60.f;
		if (time < 0) {
			action = State::Attack;
			time = attackDuration;
		}

	}
	if (action == State::Attack) {
		speed = dashSpeed;
		time -= 1 / 60.f;
		if (time < 0) {
			action = State::Follow;
			speed = followSpeed;
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

float Monster::distanceFromPlayer()
{
	sf::Vector2f dir(player->get_x() - x, player->get_y() - y);
	return std::sqrt(dir.x*dir.x + dir.y * dir.y);
}
