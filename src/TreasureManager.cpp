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

/**
 * Update the text with the numbers of treasure found.
 *
 * @param elapsed time spent since last frame.
 */
void TreasureManager::update(sf::Time elapsed)
{
	text.setString("Trésors : " + std::to_string(treasuresFoundCount) + "/" + std::to_string(treasuresCount)+ "\nPièces : " + std::to_string(coinFoundCount) + "/" + std::to_string(coinCount) + "\nO2 :");
	text.setPosition(10, 20);
	if (gameWon()) {
		player->kill(EndType::Victory); // The player is not actually dead but it makes it unable to move.
	}
}

/**
 * Display the text with treasure counts on the window.
 *
 * @param window on which the text is displayed.
 */
void TreasureManager::display(sf::RenderWindow& window) const
{
	window.draw(text);
}

/**
 * Tell the TreasureManager that a coin has been found.
 *
 * @param isCoin whether the treasure is a coin or not.
 */
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

/**
 * Generate treasures in rooms.
 *
 * @param rooms vector of rooms.
 */
void TreasureManager::createTreasures(std::vector<std::unique_ptr<Room>> const& rooms)
{
	for (int i = 0; i < coinCount; i++) {
		// Choose and random room in which the coin will be created.
		int randomId = random_1_to_n(rooms.size()) - 1;
		auto [posX, posY] = rooms[randomId]->findAvailableCoinPosition();
		rooms[randomId]->addObject(createTreasure(posX, posY, true));
	}
	for (auto const& room : rooms) {
		// Create chests for the treasure rooms.
		for (auto const& [posX, posY] : room->getTreasurePos()) {
			room->addObject(createTreasure(posX, posY, false));
		}
	}
}

/**
 * Return the number of treasures other than coins that have been found.
 * 
 * @return number of treasures.
 */
int TreasureManager::getTreasuresFoundCount() const
{
	return treasuresFoundCount;
}
/**
 * Return the number of coins have been found.
 * 
 * @return number of coins.
 */
int TreasureManager::getCoinFoundCount() const
{
	return coinFoundCount;
}

/**
 * Return true if all treasures other than coins have been found.
 * 
 * @return true if all treasures other than coins have been found.
 */
bool TreasureManager::gameWon() const
{
	return treasuresFoundCount == treasuresCount;
}

/**
 * Create a treasure.
 * 
 * @param treasureX x position of the treasure.
 * @param treasureY y position of the treasure.
 * @param isCoin true if the treasure to create is a coin.
 * @return the treasure created.
 */
std::unique_ptr<Treasure> TreasureManager::createTreasure(float treasureX, float treasureY, bool isCoin)
{
	if (isCoin) return std::make_unique<Treasure>(treasureX, treasureY, player, this, isCoin, coin_texture);
	else return std::make_unique<Treasure>(treasureX, treasureY, player, this, isCoin, chest_texture);
}



