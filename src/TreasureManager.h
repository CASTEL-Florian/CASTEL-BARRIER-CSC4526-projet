#pragma once
#include <Player.h>
#include "Treasure.h"
#include "RoomGenerator.h"


class TreasureManager {
public:
	TreasureManager(Player* player, RoomGenerator* roomGenerator);
	void displayTreasures(sf::RenderWindow& window) const;
	void update();
	void display(sf::RenderWindow& window) const;
	void findTreasure();
	std::pair<float, float> findAvailablePlace() const;
private:
	float x;
	float y;
	Player* player;
	RoomGenerator* roomGenerator;
	std::vector<std::unique_ptr<Treasure>> treasures;
	void createTreasure(float treasureX, float treasureY);
	sf::Font font;
	sf::Text text;
	int treasuresFoundCount = 0;
	int treasuresCount = 1;
	int coinFoundCount = 0;
	int coinCount = 20;
};