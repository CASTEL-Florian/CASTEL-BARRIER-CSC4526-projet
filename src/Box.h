#pragma once
#include "box2d/box2d.h"
#include <memory>
#include "SFML/Graphics.hpp"
#include <iostream>


class Box
{
public:
	Box() = default;

	void init(b2World* world, const b2Vec2& position, const b2Vec2& dimensions, b2BodyType bodyTy);
	b2Body* getBody() { return body; }
	void updateSprite();
	void renderRectangle(sf::RenderWindow& window) const;

protected:
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;
	float x;
	float y;
	float h;
	float w;
	float rota;
};