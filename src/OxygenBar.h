#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class OxygenBar
{
public:
	OxygenBar(float x, float y, float timeMax);
	void update(sf::Time elapsed);
	void display() const;
private:
	float timeMax;
	float time;
	float x;
	float y;

};

