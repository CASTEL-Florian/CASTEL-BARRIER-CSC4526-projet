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



void Treasure::update(sf::Time elapsed)
{
	if (!found && distanceFromPlayer() < playerCatchRange) {
		found = true;
		treasureManager->findTreasure(isCoin);
	}
	animator->update(elapsed);
}

void Treasure::display(sf::RenderWindow& window) const
{
	if (found)
		return;
	/*sf::RectangleShape rect;
	if (isCoin)
		rect.setSize(sf::Vector2f(2, 2));
	else
		rect.setSize(sf::Vector2f(6, 6));
	rect.setOrigin(rect.getSize() / 2.f);
	rect.setFillColor(sf::Color::Yellow);
	rect.setPosition(x, y);
	window.draw(rect);*/
	
	animator->setPosition(sf::Vector2f(x, y));
	animator->display(window);
}
float Treasure::get_x() const
{
	return x;
}

float Treasure::get_y() const
{
	return y;
}

float Treasure::distanceFromPlayer() const
{
	sf::Vector2f dir(player->get_x() - x, player->get_y() - y);
	return std::sqrt(dir.x * dir.x + dir.y * dir.y);
}
