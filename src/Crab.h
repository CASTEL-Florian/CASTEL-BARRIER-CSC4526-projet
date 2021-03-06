#pragma once
#include "Box.h"
#include "Object.h"

/**
 * Solid crab bouncing on everything.
 */
class Crab : public Box, public Object {
public:
	Crab(b2World* world, sf::Texture *texture, float scale, const b2Vec2& position);
	void initCrabBox(b2World* world, const b2Vec2& position, b2BodyType bodyTy);
	void update(sf::Time elapsed) override;
	void display(sf::RenderWindow& window) const override;
	float get_x() const override;
	float get_y() const override;
};