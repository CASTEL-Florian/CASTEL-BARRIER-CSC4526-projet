#include "Fish.h"
#include "FishSpawner.h"
#include "RoomGenerator.h"

Fish::Fish(sf::Texture* texture, FishSpawner* fishSpawner, Player* player,float scal, float x, float y) : fishSpawner(fishSpawner), player(player), x(x), y(y)
{
	
}

void Fish::update(sf::Time elapsed)
{
	actionTime -= elapsed.asSeconds();

	if (action != FishAction::Flee && distanceFromPlayer() < fleeDistance) {
		action = FishAction::Flee;
		rotateToward(2 * x - player->get_x(), 2 * y - player->get_y());
		speed = fleeSpeed;
	}
	if (action == FishAction::Flee) {
		x += std::cos(angle * b2_pi / 180) * speed * elapsed.asSeconds();
		y += std::sin(angle * b2_pi / 180) * speed * elapsed.asSeconds();
		return;
	}
	if (actionTime <= 0) {
		actionTime = actionDuration;
		action = (FishAction)(random_1_to_n(3) - 1);
	}
	if (action == FishAction::Stop) {
		if (speed > 0) {
			speed -= acceleration;
			if (speed < 0)
				speed = 0;
		}
		if (speed < 0) {
			speed += acceleration;
			if (speed > 0)
				speed = 0;
		}
	}
	else if (action == FishAction::MoveLeft) {
		speed -= acceleration;
		if (speed < -maxSpeed)
			speed = -maxSpeed;
	}
	else {
		speed += acceleration;
		if (speed > maxSpeed)
			speed = maxSpeed;
	}
	x += speed * elapsed.asSeconds();
}

void Fish::display(sf::RenderWindow& window) const
{
	sf::RectangleShape rect;
	rect.setFillColor(sf::Color::Magenta);
	rect.setSize(sf::Vector2f(5, 2));
	rect.setOrigin(rect.getSize() / 2.f);
	rect.setPosition(x, y);
	rect.setRotation(angle);
	window.draw(rect);
}

float Fish::get_x() const
{
	return x;
}

float Fish::get_y() const
{
	return y;
}

void Fish::init(float posX, float posY)
{
	x = posX;
	y = posY;
	angle = 0;
	speed = 0;
	action = FishAction::Stop;
}

float Fish::distanceFromPlayer() const
{
	sf::Vector2f dir(player->get_x() - x, player->get_y() - y);
	return std::sqrt(dir.x * dir.x + dir.y * dir.y);
}

void Fish::rotateToward(float x1, float y1)
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