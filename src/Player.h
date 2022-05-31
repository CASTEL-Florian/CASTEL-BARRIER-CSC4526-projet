#pragma once
#include "Box.h"

class Player : public Box {
public:
	explicit Player(const float enginePower);
	void move(const b2Vec2& vec);
	void renderLight(sf::RenderWindow& window) const;
private:
	float enginePower;
};