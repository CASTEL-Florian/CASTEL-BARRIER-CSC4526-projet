#pragma once
#include "Fish.h"
#include <iostream>
#include "myRandom.h"

class FishSpawner {
public:
	FishSpawner(sf::Texture* fishTexture, Player* player);
	void update(sf::Time elapsed);
	void display(sf::RenderWindow& window) const;
private:
	void spawnFish(float x, float y);
	void spawnFishRoom(int dx, int dy);
	std::vector<std::unique_ptr<Fish>> fishVector;
	std::vector<std::unique_ptr<Fish>> inactiveFish;
	sf::Texture* fishTexture;
	Player* player;
	const int maxFishInRoom = 10;
	bool closeToPlayer(float x, float y) const;
	int oldPlayerX = 0;
	int oldPlayerY = 0;
};