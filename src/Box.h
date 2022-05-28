#pragma once
#include "box2d/box2d.h"
#include <memory>
#include "SFML/Graphics.hpp"
#include <iostream>


class Box
{
public:
	Box() = default;

	void init(b2World* world, const b2Vec2& position, const b2Vec2& dimensions, const float density);
	b2Body* getBody() { return body; }
	void updateSprite();
	void render(sf::RenderWindow& window) const;

private:
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;
	float x;
	float y;
	float h;
	float w;
	float rota;
};