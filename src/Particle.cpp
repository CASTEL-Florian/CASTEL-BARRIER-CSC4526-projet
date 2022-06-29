#include "Particle.h"

/**
 * Particle.x getter
 *
 */
float Particle::get_x() const
{
	return x;
}

/**
 * Particle.y getter
 *
 */
float Particle::get_y() const
{
	return y;
}

/**
 * Initialize the position of the particle.
 *
 * @param posX x position of the particle.
 * @param posY y position of the particle.
 */
void Particle::init(float x_, float y_, float velocity, float velocityAngle, float lifetime_)
{
	x = x_;
	y = y_;
	lifetime = lifetime_;
	xSpeed = velocity * std::cos(velocityAngle);
	ySpeed = velocity * std::sin(velocityAngle);
}

/**
 * Update the particle.
 *
 * @param elapsed time since last frame.
 */
void Particle::update(sf::Time elapsed)
{
	lifetime -= elapsed.asSeconds();
	xSpeed -= xSpeed * fluidFriction * elapsed.asSeconds();
	ySpeed -= ySpeed * fluidFriction * elapsed.asSeconds();
	x += xSpeed * elapsed.asSeconds();
	y += ySpeed * elapsed.asSeconds();
}

/**
 * Particle.lifetime getter
 *
 */
float Particle::getLifetime() const
{
	return lifetime;
}

