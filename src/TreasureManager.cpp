#include "TreasureManager.h"
#include "TreasureManager.h"
#include "Treasure.h"




TreasureManager::TreasureManager(Player* player, RoomGenerator* roomGenerator, sf::Texture* coin_texture, sf::Texture* chest_texture) :
	player(player), roomGenerator(roomGenerator), coin_texture(coin_texture), chest_texture(chest_texture)
{
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
		createTreasure(pos.first, pos.second, true);
	}
}

void TreasureManager::displayTreasures(sf::RenderWindow& window) const
{
	for (auto &treasure : treasures) {
		if (closeToPlayer(treasure->get_x(), treasure->get_y()))
			treasure->display(window);
	}
}

void TreasureManager::update()
{
	text.setString("Tr�sors : " + std::to_string(treasuresFoundCount) + "/" + std::to_string(treasuresCount)+ "\nPi�ces : " + std::to_string(coinFoundCount) + "/" + std::to_string(coinCount));
	for (auto &treasure : treasures) {
		if (closeToPlayer(treasure->get_x(), treasure->get_y()))
			treasure->update();
	}
}

void TreasureManager::display(sf::RenderWindow& window) const
{
	window.draw(text);
}

void TreasureManager::findTreasure(bool isCoin)
{
	if (isCoin)
		coinFoundCount++;
	else
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

void TreasureManager::createMainTreasures(std::vector<std::unique_ptr<Room>> const& rooms)
{
	for (auto const& room : rooms) {
		for (auto const& [posX, posY] : room->getTreasurePos()) {
			createTreasure(posX, posY, false);
			treasuresCount++;
		}
	}
}

void TreasureManager::createTreasure(float treasureX, float treasureY, bool isCoin)
{
	if(isCoin) treasures.push_back(std::make_unique<Treasure>(treasureX, treasureY, player, this, isCoin, coin_texture));
	else treasures.push_back(std::make_unique<Treasure>(treasureX, treasureY, player, this, isCoin, chest_texture));
}

bool TreasureManager::closeToPlayer(float x, float y) const
{
	float roomX = std::floor(x / (roomWidth * tileWidth));
	float roomY = std::floor(y / (roomWidth * tileWidth));
	return std::abs(roomX - player->getRoomX()) + std::abs(roomY - player->getRoomY()) <= 1;
}

