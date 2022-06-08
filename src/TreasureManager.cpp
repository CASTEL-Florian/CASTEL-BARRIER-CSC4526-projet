#include "TreasureManager.h"
#include "Treasure.h"
#include "myRandom.h"




TreasureManager::TreasureManager(Player* player, sf::Texture* coin_texture, sf::Texture* chest_texture, SoundHandler* soundHandler) :
	player(player), coin_texture(coin_texture), chest_texture(chest_texture), soundHandler(soundHandler)
{
	if (!font.loadFromFile("resources/Pixeled.ttf"))
	{
		std::cout << "Erreur de chargement du fichier Pixeled.ttf";
	}
	text.setFont(font);
	text.setCharacterSize(15);
	text.setPosition(10, 10);
	text.setString(std::to_string(treasuresFoundCount));
}


void TreasureManager::update(sf::Time elapsed)
{
	text.setString("Trésors : " + std::to_string(treasuresFoundCount) + "/" + std::to_string(treasuresCount)+ "\nPièces : " + std::to_string(coinFoundCount) + "/" + std::to_string(coinCount) + "\nO2 :");
	text.setPosition(10, 20);
	if (gameWon()) {
		player->kill(EndType::Victory);
	}
}

void TreasureManager::display(sf::RenderWindow& window) const
{
	window.draw(text);
}

void TreasureManager::findTreasure(bool isCoin)
{
	if (isCoin) {
		coinFoundCount++;
		soundHandler->playCoinSound();
	}
	else {
		treasuresFoundCount++;
		soundHandler->playChestSound();
	}
}


void TreasureManager::createTreasures(std::vector<std::unique_ptr<Room>> const& rooms)
{
	for (int i = 0; i < coinCount; i++) {
		int randomId = random_1_to_n(rooms.size()) - 1;
		auto [posX, posY] = rooms[randomId]->findAvailableCoinPosition();
		rooms[randomId]->addObject(createTreasure(posX, posY, true));
	}
	for (auto const& room : rooms) {
		for (auto const& [posX, posY] : room->getTreasurePos()) {
			room->addObject(createTreasure(posX, posY, false));
		}
	}
}

int TreasureManager::getTreasuresFoundCount() const
{
	return treasuresFoundCount;
}

int TreasureManager::getCoinFoundCount() const
{
	return coinFoundCount;
}

bool TreasureManager::gameWon() const
{
	return treasuresFoundCount == treasuresCount;
}

std::unique_ptr<Treasure> TreasureManager::createTreasure(float treasureX, float treasureY, bool isCoin)
{
	if (isCoin) return std::make_unique<Treasure>(treasureX, treasureY, player, this, isCoin, coin_texture);
	else return std::make_unique<Treasure>(treasureX, treasureY, player, this, isCoin, chest_texture);
}



