#pragma once
#include <Player.h>

class TreasureManager;

class Treasure {
public:
	Treasure(float x, float y, Player* player, TreasureManager* treasureManager, bool isCoin);
	void update();
	void display(sf::RenderWindow& window) const;
private:
	float distanceFromPlayer() const;
	float x;
	float y;
	bool found = false;
	bool isCoin;
	Player* player;
	TreasureManager* treasureManager;
	float playerCatchRange = 5;
};