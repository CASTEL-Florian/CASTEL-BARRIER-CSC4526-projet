#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class OxygenBar
{
public:
	OxygenBar(float x, float y, float timeMax);
	void update(sf::Time elapsed);
	void display(sf::RenderWindow& window) const;
private:
	float timeMax;
	float time;
	float x;
	float y;
	const float height = 200;
	const float width = 10;

};

