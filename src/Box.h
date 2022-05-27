#pragma once
#include "box2d/box2d.h"

class Box
{
public:
	Box();

	void init(b2World* world, const b2Vec2& position, const b2Vec2& dimensions);

private:
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;
};