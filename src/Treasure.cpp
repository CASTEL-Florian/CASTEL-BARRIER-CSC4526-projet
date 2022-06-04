#include "Treasure.h"
#include "TreasureManager.h"

Treasure::Treasure(float x, float y, Player* player, TreasureManager* treasureManager, bool isCoin, sf::Texture* texture) : 
	x(x), y(y), player(player), treasureManager(treasureManager), isCoin(isCoin), texture(texture)
{
}



void Treasure::update()
{
	if (!found && distanceFromPlayer() < playerCatchRange) {
		found = true;
		treasureManager->findTreasure(isCoin);
	}
	animSprite();
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
	
	sf::Sprite sprite;
	sprite.setTexture(*texture);
	if(isCoin) sprite.setTextureRect(sf::IntRect(rectOffset, 0, 16, 16));
	else sprite.setTextureRect(sf::IntRect(rectOffset, 0, 32, 32));
	sprite.setScale(sf::Vector2f(0.2f, 0.2f));
	sf::FloatRect bounds = sprite.getLocalBounds();
	float wi = bounds.width;
	float hi = bounds.height;
	sprite.setOrigin(sf::Vector2f(wi, hi) / 2.f);
	sprite.setPosition(sf::Vector2f(x, y));
	window.draw(sprite);
}
float Treasure::get_x() const
{
	return x;
}

float Treasure::get_y() const
{
	return y;
}

void Treasure::animSprite() {
	if (isCoin) {
		if (animTimer.getElapsedTime().asMilliseconds() >= 100) {
			rectOffset += 16;
			if (rectOffset >= 208) {
				rectOffset = 0;
			}
			animTimer.restart();
		}
	}
	else {
		if (animTimer.getElapsedTime().asMilliseconds() >= 100) {
			rectOffset += 32;
			if (rectOffset >= 352) {
				rectOffset = 0;
			}
			animTimer.restart();
		}
	}
}

float Treasure::distanceFromPlayer() const
{
	sf::Vector2f dir(player->get_x() - x, player->get_y() - y);
	return std::sqrt(dir.x * dir.x + dir.y * dir.y);
}
