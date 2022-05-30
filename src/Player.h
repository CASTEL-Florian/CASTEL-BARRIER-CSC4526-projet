#pragma once
#include "Box.h"

class Player : public Box {
public:
	explicit Player(const float enginePower);
	void move(const b2Vec2& vec);
private:
	float enginePower;
};