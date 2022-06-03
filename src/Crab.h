#pragma once
#include "Box.h"

class Crab : public Box {
public:
	Crab() = default;
	void initSprite(sf::Texture* textur, const float scal) override;
	void initBox(b2World* world, const b2Vec2& position, b2BodyType bodyTy) override;
	void update() override;
	void renderSprite(sf::RenderWindow& window) const override;
	void animSprite();
private:
	int rectOffset = 0;
	sf::Clock animTimer;
};