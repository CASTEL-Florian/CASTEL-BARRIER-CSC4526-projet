#include "Minimap.h"


Minimap::Minimap(const std::string& filename)
{
	if (!minimapTextures.loadFromFile(filename)) {
		std::cout << "Erreur de chargement de la texture : " << filename << "\n";
	}
}

/**
 * Display the minimap on the window.
 *
 * @param window on which the minimap is drawn.
 */
void Minimap::display(sf::RenderWindow& window, std::vector<std::unique_ptr<Room>> const& rooms) const
{
	sf::Sprite sprite;
	sprite.setScale(scale, scale);
	sprite.setTexture(minimapTextures);
	for (auto const &room : rooms) {
		// Only display on the minimap rooms that the player already visited.
		if (!room->isExplored())
			continue;

		// Find the right sprite.
		int sprite_id = 0;
		for (int direction = 3; direction >= 0; direction--) {
			sprite_id *= 2;
			if (room->is_opened(direction)) {
				sprite_id += 1;
			}
		}
		sprite.setTextureRect(sf::IntRect((sprite_id%4) * spriteLenght, (int)(sprite_id / 4) * spriteHeight, spriteLenght, spriteHeight));
		sprite.setPosition(sf::Vector2f(x + room->get_x() * spriteLenght * scale, y + room->get_y() * spriteHeight * scale));
		window.draw(sprite);
	}

	// Draw a circle on the minimap to indicate the position of the player.
	sf::CircleShape playerIndicator(playerIndicatorRadius);
	playerIndicator.setPosition(sf::Vector2f(x + px * spriteLenght * scale - playerIndicatorRadius / 2, x + py * spriteHeight * scale - playerIndicatorRadius / 2));
	playerIndicator.setFillColor(sf::Color::Red);
	window.draw(playerIndicator);
}

/**
 * Update player poistion on the minimap.
 *
 * @param playerX x position of the player.
 * @param playerY y position of the player.
 */
void Minimap::updatePlayerPosition(float playerX, float playerY)
{
	px = playerX / (roomWidth * tileWidth);
	py = playerY / (roomHeight * tileHeight);
}
