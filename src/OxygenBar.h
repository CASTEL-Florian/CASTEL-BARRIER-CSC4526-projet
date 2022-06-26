#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"

/**
 * Oxygen bar that gradually empties before killing the player.
 */
class OxygenBar
{
public:
	OxygenBar(float x, float y, float timeMax, Player* player);
	void update(sf::Time elapsed);
	void display(sf::RenderWindow& window) const;
	void refill(float amount);
private:
	Player* player;
	float timeMax;
	float time;
	float x;
	float y;
	const float boostMultiplier = 3;
	const float height = 200;
	const float width = 10;

};

