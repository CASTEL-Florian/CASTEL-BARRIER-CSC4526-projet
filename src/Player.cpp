#include "Player.h"

Player::Player(const float enginePower) :
	enginePower(enginePower)
{
}

//test d'application d'une force au nez du sous-marin
void Player::move(const b2Vec2& vec) {
	body->ApplyForce(b2Vec2(vec.x * enginePower, vec.y * enginePower), 
		body->GetPosition() + b2Vec2(w * std::cos(body->GetAngle()) / 10, w *std::sin(body->GetAngle()) / 10),
		//b2Vec2(w / 2, 0),
		true);
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