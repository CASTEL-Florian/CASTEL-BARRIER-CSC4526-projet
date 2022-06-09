#pragma once
#include "Box.h"
#include "Object.h"
#include "Animator.h"

class Crate : public Box, public Object {
public:
	Crate(b2World* world, sf::Texture* texture, float scal, const b2Vec2& position);
	void update(sf::Time elapsed) override;
	void display(sf::RenderWindow& window) const override;
	float get_x() const override;
	float get_y() const override;
};