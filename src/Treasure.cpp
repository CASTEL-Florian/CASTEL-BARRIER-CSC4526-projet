#include "Treasure.h"
#include "TreasureManager.h"

Treasure::Treasure(float x, float y, Player* player, TreasureManager* treasureManager, bool isCoin, sf::Texture* texture) : 
	x(x), y(y), player(player), treasureManager(treasureManager), isCoin(isCoin)
{
	int spriteLength = 32;
	int numberOfImages = 12;
	if (isCoin) {
		spriteLength = 16;
		numberOfImages = 14;
	}
	animator = std::make_unique<Animator>(texture, 0.2f, spriteLength, spriteLength, 0.1f, std::vector<int> {numberOfImages});
}

/**
 * Update found value and call update of animator.
 *
 * @param elapsed time elapsed since last frame
 */
void Treasure::update(sf::Time elapsed)
{
	if (!found && distanceFromPlayer() < playerCatchRange) {
		found = true;
		treasureManager->findTreasure(isCoin);
	}
	animator->update(elapsed);
}

/**
 * Display the treasure if not yet found.
 *
 * @param window window in which to render
 */
void Treasure::display(sf::RenderWindow& window) const
{
	if (found)
		return;
	animator->setPosition(sf::Vector2f(x, y));
	animator->display(window);
}

/**
 * Treasure.x getter.
 *
 */
float Treasure::get_x() const
{
	return x;
}

/**
 * Treasure.y getter.
 *
 */
float Treasure::get_y() const
{
	return y;
}

/**
 * Calculate distance between treasure and player.
 *
 */
float Treasure::distanceFromPlayer() const
{
	sf::Vector2f dir(player->get_x() - x, player->get_y() - y);
	return std::sqrt(dir.x * dir.x + dir.y * dir.y);
}
