#include "Particle.h"

float Particle::get_x() const
{
	return x;
}

float Particle::get_y() const
{
	return y;
}

void Particle::init(float x_, float y_, float velocity, float velocityAngle, float lifetime_)
{
	x = x_;
	y = y_;
	lifetime = lifetime_;
	xSpeed = velocity * std::cos(velocityAngle);
	ySpeed = velocity * std::sin(velocityAngle);
}

void Particle::update(sf::Time elapsed)
{
	lifetime -= elapsed.asSeconds();
	xSpeed -= xSpeed * fluidFriction * elapsed.asSeconds();
	ySpeed -= ySpeed * fluidFriction * elapsed.asSeconds();
	x += xSpeed * elapsed.asSeconds();
	y += ySpeed * elapsed.asSeconds();
}

float Particle::getLifetime() const
{
	return lifetime;
}

