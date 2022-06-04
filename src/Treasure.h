#pragma once
#include <Player.h>

class TreasureManager;

class Treasure {
public:
	Treasure(float x, float y, Player* player, TreasureManager* treasureManager, bool isCoin, sf::Texture* texture);
	void update();
	void display(sf::RenderWindow& window) const;
	float get_x() const;
	float get_y() const;
private:
	float distanceFromPlayer() const;
	void animSprite();
	float x;
	float y;
	bool found = false;
	bool isCoin;
	Player* player;
	TreasureManager* treasureManager;
	float playerCatchRange = 5;

	sf::Texture* texture;
	int rectOffset = 0;
	sf::Clock animTimer;
};