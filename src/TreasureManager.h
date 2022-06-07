#pragma once
#include <Player.h>
#include "Treasure.h"
#include "RoomGenerator.h"
#include "SoundHandler.h"

const int coinCount = 20;
const int treasuresCount = 5;
class TreasureManager {
public:
	TreasureManager(Player* player, sf::Texture* coin_texture, sf::Texture* chest_texture, SoundHandler* soundHandler);
	void update(sf::Time elapsed);
	void display(sf::RenderWindow& window) const;
	void findTreasure(bool isCoin);
	void createTreasures(std::vector<std::unique_ptr<Room>> const& rooms);
	int getTreasuresFoundCount() const;
	int getCoinFoundCount() const;
private:
	float x;
	float y;
	Player* player;
	std::unique_ptr<Treasure> createTreasure(float treasureX, float treasureY, bool isCoin);
	sf::Font font;
	sf::Text text;
	int treasuresFoundCount = 0;
	int coinFoundCount = 0;
	
	sf::Texture* coin_texture;
	sf::Texture* chest_texture;

	SoundHandler* soundHandler;
};