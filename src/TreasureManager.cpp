#include "TreasureManager.h"
#include "Treasure.h"

TreasureManager::TreasureManager(Player* player, RoomGenerator* roomGenerator) : player(player), roomGenerator(roomGenerator) {
	//createTreasure(player->get_x(), 30);
	if (!font.loadFromFile("resources/Roboto-Regular.ttf"))
	{
		std::cout << "Erreur de chargement du fichier Roboto-Regular.ttf";
	}
	text.setFont(font);
	text.setCharacterSize(30);
	text.setPosition(10, 10);
	text.setString(std::to_string(treasuresFoundCount));
	for (int i = 0; i < coinCount; i++) {
		auto pos = findAvailablePlace();
		createTreasure(pos.first, pos.second);
	}
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

std::pair<float, float> TreasureManager::findAvailablePlace () const
{
	auto roomPos = roomGenerator->getRandomRoomPos();
	std::pair<float, float> pos(roomPos.first * roomWidth * tileWidth, roomPos.second * roomHeight * tileHeight);
	pos.first += (random_1_to_n(roomWidth - 2) + 0.5f) * tileWidth;
	pos.second += (random_1_to_n(roomHeight - 2) + 0.5f) * tileHeight;
	return pos;
}

void TreasureManager::createTreasure(float treasureX, float treasureY)
{
	treasures.push_back(std::make_unique<Treasure>(treasureX, treasureY, player, this));
}
