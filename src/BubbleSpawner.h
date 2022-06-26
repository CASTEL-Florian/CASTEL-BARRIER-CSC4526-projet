#pragma once
#include "Bubble.h"
#include <iostream>
#include "myRandom.h"
#include "OxygenBar.h"

/**
 * Class dealing with Fish creation and object pooling
 */
class BubbleSpawner {
public:
	BubbleSpawner(sf::Texture* bubbleTexture, Player* player, OxygenBar* oxygenBar);
	void update(sf::Time elapsed);
	void display(sf::RenderWindow& window) const;
private:
	void spawnBubble(float x, float y);
	std::vector<std::unique_ptr<Bubble>> bubbleVector;
	std::vector<std::unique_ptr<Bubble>> inactiveBubbles;
	sf::Texture* bubbleTexture;
	OxygenBar* oxygenBar;
	Player* player;
	const float minSpawnRadius = 30;
	const float maxSpawnRadius = 150;
	const float timeBetweenSpawn = 1.f;
	float time = 0;
};