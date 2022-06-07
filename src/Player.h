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
	bool isAlive() const;
	void kill(sf::Color transitionCol);
	sf::Color getTransitionColor();
private:
	float enginePower;
	int roomX = 0;
	int roomY = 0;
	int rectOffset = 0;
	bool alive = true;
	std::unique_ptr<Animator> animator;
	sf::Color transitionColor = sf::Color::Yellow;
};