#pragma once
#include "Box.h"
#include "Animator.h"
#include "Object.h"

class Crab : public Box, public Object {
public:
	Crab(b2World* world, sf::Texture *texture, float scal, const b2Vec2& position);
	void initCrabBox(b2World* world, const b2Vec2& position, b2BodyType bodyTy);
	void update(sf::Time elapsed) override;
	void display(sf::RenderWindow& window) const override;
private:
	std::unique_ptr<Animator> animator;
};