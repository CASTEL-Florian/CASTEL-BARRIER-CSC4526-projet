#pragma once
#include <Player.h>
#include "Treasure.h"


class TreasureManager {
public:
	TreasureManager(Player* player);
	void displayTreasures(sf::RenderWindow& window) const;
	void update();
	void display(sf::RenderWindow& window) const;
	void findTreasure();
private:
	float x;
	float y;
	Player* player;
	std::vector<std::unique_ptr<Treasure>> treasures;
	void createTreasure(float treasureX, float treasureY);
	sf::Font font;
	sf::Text text;
	int treasuresFoundCount = 0;
	int treasuresCount = 1;
};