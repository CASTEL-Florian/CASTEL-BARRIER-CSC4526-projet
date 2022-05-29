#pragma once
#include "Box.h"

class Player : public Box {
public:
	explicit Player(const float enginePower);
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
	void rotateRight();
	void rotateLeft();
private:
	float enginePower;
};