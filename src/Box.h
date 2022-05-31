#pragma once
#include "box2d/box2d.h"
#include <memory>
#include "SFML/Graphics.hpp"
#include <iostream>


class Box
{
public:
	Box() = default;

	void init(b2World* world, const b2Vec2& position, b2BodyType bodyType, sf::Texture& textur, const float scal);
	void init(b2World* world, const b2Vec2& position, b2BodyType bodyType, const float scal, const b2Vec2& dimensions = b2Vec2(0.f, 0.f));
	void initSprite(sf::Texture& texture, const float scal);
	void initBox(b2World* world, const b2Vec2& position, b2BodyType bodyTy);
	
	void updateSprite();
	void renderRectangle(sf::RenderWindow& window) const;
	void renderSprite(sf::RenderWindow& window) const;
	float get_x() const;
	float get_y() const;

protected:
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;
	float x = 0.0f;
	float y = 0.0f;
	float h = 0.0f;
	float w = 0.0f;
	float rota = 0.0f;
	float scale = 0.0f;
	sf::Texture texture;
};