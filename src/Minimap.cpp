#include "Minimap.h"


Minimap::Minimap(const std::string filename)
{
	if (!minimapTextures.loadFromFile(filename)) {
		std::cout << "Erreur de chargement de la texture : " << filename << "\n";
	}
}

void Minimap::display(sf::RenderWindow& window, std::vector<std::unique_ptr<Room>> const& rooms) const
{
	sf::Sprite sprite;
	sprite.setScale(scale, scale);
	sprite.setTexture(minimapTextures);
	for (auto const &room : rooms) {
		if (!room->isExplored())
			continue;
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
	sf::CircleShape playerIndicator(playerIndicatorRadius);
	playerIndicator.setPosition(sf::Vector2f(x + px * spriteLenght * scale - playerIndicatorRadius / 2, x + py * spriteHeight * scale - playerIndicatorRadius / 2));
	playerIndicator.setFillColor(sf::Color::Red);
	window.draw(playerIndicator);
}

void Minimap::updatePlayerPosition(float playerX, float playerY)
{
	px = playerX / (roomWidth * tileWidth);
	py = playerY / (roomHeight * tileHeight);
}
