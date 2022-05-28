#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <Room.h>

class Minimap
{
public:
	explicit Minimap(const std::string filename);
	void display(sf::RenderWindow& window, const std::vector<std::unique_ptr<Room>>& rooms) const;
private:
	sf::Texture minimapTextures;
	float x = 200;
	float y = 200;
	float scale = 2;
	int const spriteLenght = 11;
	int const spriteHeight = 11;
};