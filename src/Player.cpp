#include "Player.h"

Player::Player(const float enginePower) :
	enginePower(enginePower)
{
}

void Player::moveUp() {
	body->ApplyForceToCenter(b2Vec2(0, enginePower), true);
}

void Player::moveDown() {
	body->ApplyForceToCenter(b2Vec2(0, -enginePower), true);
}

void Player::moveRight() {
	float movX = std::cos(body->GetAngle()) * enginePower;
	float movY = std::sin(body->GetAngle()) * enginePower;
	body->ApplyForceToCenter(b2Vec2(movX, movY), true);
}

void Player::moveLeft() {
	float movX = -std::cos(body->GetAngle()) * enginePower;
	float movY = -std::sin(body->GetAngle()) * enginePower;
	body->ApplyForceToCenter(b2Vec2(movX, movY), true);
}

void Player::rotateRight() {
	body->ApplyTorque(-enginePower / 2, true);
}

void Player::rotateLeft() {
	body->ApplyTorque(enginePower / 2, true);
}