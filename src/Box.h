#pragma once
#include "box2d/box2d.h"
#include <memory>
#include "SFML/Graphics.hpp"
#include <iostream>


class Box
{
public:
	Box() = default;

	void init(b2World* world, const b2Vec2& position, b2BodyType bodyType, const b2Vec2& dimensions);
	virtual void initBox(b2World* world, const b2Vec2& position, b2BodyType bodyTy);
	
	virtual void update(sf::Time elapsed);
	void renderRectangle(sf::RenderWindow& window) const;
	virtual ~Box() = default;

protected:
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;
	float x = 0.0f;
	float y = 0.0f;
	float h = 0.0f;
	float w = 0.0f;
	float rota = 0.0f;
};