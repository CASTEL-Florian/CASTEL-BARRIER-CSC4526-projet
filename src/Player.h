#pragma once
#include "Box.h"
#include "Room.h"
#include "Animator.h"
#include "Object.h"

class Player : public Box, public Object {
public:
	Player(b2World* world, const float enginePower, sf::Texture* texture, float scale);
	void move(const b2Vec2& vec);
	void update(sf::Time elapsed) override;
	void renderLight(sf::RenderWindow& window) const;
	void display(sf::RenderWindow& window) const override;
	void updateRoomPosition();
	int getRoomX() const;
	int getRoomY() const;
	float get_x() const override;
	float get_y() const override;
private:
	float enginePower;
	int roomX;
	int roomY;
	int rectOffset = 0;
	std::unique_ptr<Animator> animator;
};