#pragma once
#include "Box.h"
#include "Room.h"

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
};