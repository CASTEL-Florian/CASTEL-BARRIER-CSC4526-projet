#include "Minimap.h"


Minimap::Minimap(const std::string filename)
{
	if (!minimapTextures.loadFromFile(filename)) {
		std::cout << "Erreur de chargement de la texture : " << filename << "\n";
	}
}

void Minimap::display(sf::RenderWindow& window, const std::vector<std::unique_ptr<Room>>& rooms) const
{
	sf::Sprite sprite;
	sprite.setScale(scale, scale);
	sprite.setTexture(minimapTextures);
	for (auto const &room : rooms) {
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
}
