#include "Particle.h"

float Particle::get_x() const
{
	return x;
}

float Particle::get_y() const
{
	return y;
}

void Particle::init(float x_, float y_, float velocity, float velocityAngle, float lifeTime_)
{
	x = x_;
	y = y_;
	lifeTime = lifeTime_;
	xSpeed = velocity * std::cos(velocityAngle);
	ySpeed = velocity * std::sin(velocityAngle);
}

void Particle::update(sf::Time elapsed)
{
	lifeTime -= elapsed.asSeconds();
	x += xSpeed * elapsed.asSeconds();
	y += ySpeed * elapsed.asSeconds();
}

float Particle::getLifeTime() const
{
	return lifeTime;
}

