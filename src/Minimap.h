#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <Room.h>

class Minimap
{
public:
	explicit Minimap(const std::string filename);
	void display(sf::RenderWindow& window, const std::vector<std::unique_ptr<Room>>& rooms) const;
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
	const int roomWidth = 15;
	const int roomHeight = 15;
	const int tileWidth = 3;
	const int tileHeight = 3;
	const float playerIndicatorRadius = 3;
};