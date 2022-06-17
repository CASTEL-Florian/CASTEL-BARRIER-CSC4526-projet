#pragma once
#include <SFML/Graphics.hpp>

class Particle {
public:
	Particle();
	float get_x() const;
	float get_y() const;
	void init(float x_, float y_, float velocity, float velocityAngle, float lifeTime);
	void update(sf::Time elapsed);
	float getLifeTime() const;
private:
	float x;
	float y;
	float xSpeed;
	float ySpeed;
	float lifeTime = 0;
};