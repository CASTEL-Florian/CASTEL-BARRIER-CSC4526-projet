#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <Room.h>

/**
 * Minimap showning on the window the layout of the rooms and the position of the player on the map.
 */
class Minimap
{
public:
	explicit Minimap(const std::string filename);
	void display(sf::RenderWindow& window, std::vector<std::unique_ptr<Room>> const& rooms) const;
	void updatePlayerPosition(float playerX, float playerY);
private:
	sf::Texture minimapTextures;
	float x = 200;
	float y = 200;
	float px = 0;
	float py = 0;
	float scale = 2;
	int const spriteLenght = 11;
	int const spriteHeight = 11;
	const float playerIndicatorRadius = 3;
};