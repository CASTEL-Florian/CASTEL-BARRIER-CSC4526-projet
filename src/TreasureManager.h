#pragma once
#include <Player.h>
#include "Treasure.h"
#include "RoomGenerator.h"


class TreasureManager {
public:
	TreasureManager(Player* player, RoomGenerator* roomGenerator, sf::Texture* coin_texture, sf::Texture* chest_texture);
	void displayTreasures(sf::RenderWindow& window) const;
	void update();
	void display(sf::RenderWindow& window) const;
	void findTreasure(bool isCoin);
	std::pair<float, float> findAvailablePlace() const;
	void createMainTreasures(std::vector<std::unique_ptr<Room>> const& rooms);
private:
	float x;
	float y;
	Player* player;
	RoomGenerator* roomGenerator;
	std::vector<std::unique_ptr<Treasure>> treasures;
	void createTreasure(float treasureX, float treasureY, bool isCoin);
	sf::Font font;
	sf::Text text;
	int treasuresFoundCount = 0;
	int treasuresCount = 0;
	int coinFoundCount = 0;
	const int coinCount = 20;
	sf::Texture* coin_texture;
	sf::Texture* chest_texture;
	bool closeToPlayer(float x, float y) const;
};