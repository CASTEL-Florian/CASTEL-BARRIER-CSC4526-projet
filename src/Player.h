#pragma once
#include "Box.h"
#include "Room.h"

class Player : public Box {
public:
	explicit Player(const float enginePower);
	void initSprite(sf::Texture* textur, const float scal) override;
	void move(const b2Vec2& vec);
	void update() override;
	void renderLight(sf::RenderWindow& window) const;
	void renderSprite(sf::RenderWindow& window) const override;
	void animSprite();
	void updateRoomPosition();
	int getRoomX() const;
	int getRoomY() const;
private:
	float enginePower;
	int roomX;
	int roomY;
	int rectOffset = 0;
	sf::Clock animTimer;
};