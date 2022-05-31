#pragma once
#include "Box.h"

class Player : public Box {
public:
	explicit Player(const float enginePower);
	void move(const b2Vec2& vec);
	void renderLight(sf::RenderWindow& window) const;
	void updateRoomPosition();
	int getRoomX() const;
	int getRoomY() const;
private:
	float enginePower;
	int roomX;
	int roomY;
	const int roomWidth = 15;
	const int roomHeight = 15;
	const int tileWidth = 3;
	const int tileHeight = 3;
};