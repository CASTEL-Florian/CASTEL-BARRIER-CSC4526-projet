#include "TreasureManager.h"
#include "Treasure.h"

TreasureManager::TreasureManager(Player* player) : player(player) {
	createTreasure(player->get_x(), 30);
	if (!font.loadFromFile("resources/Roboto-Regular.ttf"))
	{
		std::cout << "Erreur de chargement du fichier Roboto-Regular.ttf";
	}
	text.setFont(font);
	text.setCharacterSize(30);
	text.setPosition(10, 10);
	text.setString(std::to_string(treasuresFoundCount));
}

void TreasureManager::displayTreasures(sf::RenderWindow& window) const
{
	for (auto &treasure : treasures) {
		treasure->display(window);
	}
}

void TreasureManager::update()
{
	text.setString(std::to_string(treasuresFoundCount) + "/" + std::to_string(treasuresCount));
	for (auto &treasure : treasures) {
		treasure->update();
	}
}

void TreasureManager::display(sf::RenderWindow& window) const
{
	window.draw(text);
}

void TreasureManager::findTreasure()
{
	treasuresFoundCount++;
}

void TreasureManager::createTreasure(float treasureX, float treasureY)
{
	treasures.push_back(std::make_unique<Treasure>(treasureX, treasureY, player, this));
}
