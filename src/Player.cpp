#include "Player.h"
#include <cmath>


Player::Player(const float enginePower) :
	enginePower(enginePower)
{
}

void Player::move(const b2Vec2& vec) {
	body->ApplyForce(b2Vec2(vec.x * enginePower, vec.y * enginePower), 
		body->GetPosition() + b2Vec2(w * std::cos(body->GetAngle()) / 5, w *std::sin(body->GetAngle()) / 5),
		true);
}

void Player::renderLight(sf::RenderWindow& window) const {
	sf::ConvexShape polygon1;
	polygon1.setPointCount(7);
	polygon1.setPoint(0, sf::Vector2f(0, 0));
	polygon1.setPoint(1, sf::Vector2f(0, 170));
	polygon1.setPoint(2, sf::Vector2f(65, 170));
	polygon1.setPoint(3, sf::Vector2f(85, 90));
	polygon1.setPoint(4, sf::Vector2f(105, 170));
	polygon1.setPoint(5, sf::Vector2f(170, 170));
	polygon1.setPoint(6, sf::Vector2f(170, 0));
	polygon1.setFillColor(sf::Color(0, 0, 15, 230));
	polygon1.setOrigin(sf::Vector2f(85, 90));
	polygon1.setRotation(rota * 180.0f / b2_pi - 90.f);
	polygon1.setPosition(x + w / 2 * std::cos(rota), y + w / 2 * std::sin(rota));
	window.draw(polygon1);

	sf::ConvexShape polygon2;
	polygon2.setPointCount(7);
	polygon2.setPoint(0, sf::Vector2f(92.5f, 120));
	polygon2.setPoint(1, sf::Vector2f(90, 122.5f));
	polygon2.setPoint(2, sf::Vector2f(85, 124.f));
	polygon2.setPoint(3, sf::Vector2f(80, 122.5f));
	polygon2.setPoint(4, sf::Vector2f(77.5f, 120));
	polygon2.setPoint(5, sf::Vector2f(65, 170));
	polygon2.setPoint(6, sf::Vector2f(105, 170));
	polygon2.setFillColor(sf::Color(0, 0, 15, 230));
	polygon2.setOrigin(sf::Vector2f(85, 90));
	polygon2.setRotation(rota * 180.0f / b2_pi - 90.f);
	polygon2.setPosition(x + w / 2 * std::cos(rota), y + w / 2 * std::sin(rota));
	window.draw(polygon2);
}

void Player::updateRoomPosition()
{
	roomX = std::floor(x / (roomWidth * tileWidth));
	roomY = std::floor(y / (roomHeight * tileHeight));
}

int Player::getRoomX() const
{
	return roomX;
}

int Player::getRoomY() const
{
	return roomY;
}
