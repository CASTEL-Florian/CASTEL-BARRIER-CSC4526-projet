#pragma once
#include <Player.h>

class TreasureManager;

class Treasure {
public:
	Treasure(float x, float y, Player* player, TreasureManager* treasureManager);
	void update();
	void display(sf::RenderWindow& window) const;
private:
	float distanceFromPlayer() const;
	float x;
	float y;
	bool found = 0;
	Player* player;
	TreasureManager* treasureManager;
	float playerCatchRange = 5;
};