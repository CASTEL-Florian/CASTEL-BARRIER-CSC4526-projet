#include "Treasure.h"
#include "TreasureManager.h"

Treasure::Treasure(float x, float y, Player* player, TreasureManager* treasureManager) : x(x), y(y), player(player), treasureManager(treasureManager)
{
}



void Treasure::update()
{
	if (!found && distanceFromPlayer() < playerCatchRange) {
		found = true;
		treasureManager->findTreasure();
	}
}

void Treasure::display(sf::RenderWindow& window) const
{
	if (found)
		return;
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(2, 2));
	rect.setOrigin(rect.getSize() / 2.f);
	rect.setFillColor(sf::Color::Yellow);
	rect.setPosition(x, y);
	window.draw(rect);
}

float Treasure::distanceFromPlayer() const
{
	sf::Vector2f dir(player->get_x() - x, player->get_y() - y);
	return std::sqrt(dir.x * dir.x + dir.y * dir.y);
}
