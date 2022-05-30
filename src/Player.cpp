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