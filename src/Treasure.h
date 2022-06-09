#pragma once
#include <Player.h>

class TreasureManager;

class Treasure : public Object {
public:
	Treasure(float x, float y, Player* player, TreasureManager* treasureManager, bool isCoin, sf::Texture* texture);
	void update(sf::Time elapsed) override;
	void display(sf::RenderWindow& window) const override;
	float get_x() const override;
	float get_y() const override;
private:
	float distanceFromPlayer() const;
	float x;
	float y;
	bool found = false;
	bool isCoin;
	Player* player;
	TreasureManager* treasureManager;
	float playerCatchRange = 7;

	
};