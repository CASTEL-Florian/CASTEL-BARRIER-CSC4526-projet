#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"

class OxygenBar
{
public:
	OxygenBar(float x, float y, float timeMax, Player* player);
	void update(sf::Time elapsed);
	void display(sf::RenderWindow& window) const;
private:
	Player* player;
	float timeMax;
	float time;
	float x;
	float y;
	const float height = 200;
	const float width = 10;

};

