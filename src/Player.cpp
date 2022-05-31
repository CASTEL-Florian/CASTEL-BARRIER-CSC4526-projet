#include "Player.h"

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
	polygon1.setPoint(1, sf::Vector2f(0, 130));
	polygon1.setPoint(2, sf::Vector2f(50, 130));
	polygon1.setPoint(3, sf::Vector2f(65, 70));
	polygon1.setPoint(4, sf::Vector2f(80, 130));
	polygon1.setPoint(5, sf::Vector2f(130, 130));
	polygon1.setPoint(6, sf::Vector2f(130, 0));
	polygon1.setFillColor(sf::Color(0, 0, 15, 230));
	polygon1.setOrigin(sf::Vector2f(65, 70));
	polygon1.setRotation(rota * 180.0f / b2_pi - 90.f);
	polygon1.setPosition(x + w / 2 * std::cos(rota), y + h / 2 * std::sin(rota));
	window.draw(polygon1);

	sf::ConvexShape polygon2;
	polygon2.setPointCount(6);
	polygon2.setPoint(0, sf::Vector2f(72.5f, 100));
	polygon2.setPoint(1, sf::Vector2f(70, 102.5f));
	polygon2.setPoint(2, sf::Vector2f(60, 102.5f));
	polygon2.setPoint(3, sf::Vector2f(57.5f, 100));
	polygon2.setPoint(4, sf::Vector2f(50, 130));
	polygon2.setPoint(5, sf::Vector2f(80, 130));
	polygon2.setFillColor(sf::Color(0, 0, 15, 230));
	polygon2.setOrigin(sf::Vector2f(65, 70));
	polygon2.setRotation(rota * 180.0f / b2_pi - 90.f);
	polygon2.setPosition(x + w / 2 * std::cos(rota), y + h / 2 * std::sin(rota));
	window.draw(polygon2);
}