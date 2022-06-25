#pragma once
#include <SFML/Graphics.hpp>

class Particle {
public:
	Particle() = default;
	float get_x() const;
	float get_y() const;
	void init(float x_, float y_, float velocity, float velocityAngle, float lifetime);
	void update(sf::Time elapsed);
	float getLifetime() const;
private:
	float x;
	float y;
	float xSpeed;
	float ySpeed;
	float lifetime = 0;
	const float fluidFriction = 1.f;
};