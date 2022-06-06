#include "TreasureManager.h"
#include "Treasure.h"




TreasureManager::TreasureManager(Player* player, RoomGenerator* roomGenerator, sf::Texture* coin_texture, sf::Texture* chest_texture) :
	player(player), roomGenerator(roomGenerator), coin_texture(coin_texture), chest_texture(chest_texture)
{
	if (!font.loadFromFile("resources/Roboto-Regular.ttf"))
	{
		std::cout << "Erreur de chargement du fichier Roboto-Regular.ttf";
	}
	text.setFont(font);
	text.setCharacterSize(30);
	text.setPosition(10, 10);
	text.setString(std::to_string(treasuresFoundCount));
}


void TreasureManager::update(sf::Time elapsed)
{
	text.setString("Trésors : " + std::to_string(treasuresFoundCount) + "/" + std::to_string(treasuresCount)+ "\nPièces : " + std::to_string(coinFoundCount) + "/" + std::to_string(coinCount));
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


void TreasureManager::createTreasures(std::vector<std::unique_ptr<Room>> const& rooms)
{
	for (int i = 0; i < coinCount; i++) {
		int randomId = random_1_to_n(rooms.size()) - 1;
		std::pair<float, float> pos(rooms[randomId]->get_x() * roomWidth * tileWidth, rooms[randomId]->get_y() * roomHeight * tileHeight);
		pos.first += (random_1_to_n(roomWidth - 2) + 0.5f) * tileWidth;
		pos.second += (random_1_to_n(roomHeight - 2) + 0.5f) * tileHeight;
		rooms[randomId]->addObject(createTreasure(pos.first, pos.second, true));
	}
	for (auto const& room : rooms) {
		for (auto const& [posX, posY] : room->getTreasurePos()) {
			room->addObject(createTreasure(posX, posY, false));
		}
	}
}

std::unique_ptr<Treasure> TreasureManager::createTreasure(float treasureX, float treasureY, bool isCoin)
{
	if (isCoin) return std::make_unique<Treasure>(treasureX, treasureY, player, this, isCoin, coin_texture);
	else return std::make_unique<Treasure>(treasureX, treasureY, player, this, isCoin, chest_texture);
}



