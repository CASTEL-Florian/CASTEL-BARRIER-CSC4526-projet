#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Particle.h"

class ParticleSystem {
public:
	ParticleSystem(sf::Texture* texture, float scale);
	void update(sf::Time elapsed);
	void display(sf::RenderWindow& window) const;
	void setPosition(sf::Vector2f pos);
	void setRotation(float angle);
	void setActive(bool flag);
private:
	void spawnParticle();
	float alphaFromLifetime(float x) const;
	float x = 0;
	float y = 0;
	float angle = 0;
	const float speed = 10;
	const float timeBetweenSpawns = 0.1f;
	const float dAngle = 0.5f;
	const float particleLifetime = 1.f;
	float time = 0;
	bool active = false;
	sf::Texture* texture;
	std::vector<std::unique_ptr<Particle>> particles;
	std::vector<std::unique_ptr<Particle>> inactiveParticles;
};