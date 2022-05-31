#pragma once
#include <utility>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TileMap.h"
#include "Box.h"
class Room
{
public:
	Room(int x, int y);
	void open_path(std::pair<int, int> const& target);
	void display(sf::RenderWindow &window) const;
	std::pair<int,int> get_position() const;
	bool is_opened(int direction);
	int get_x() const;
	int get_y() const;
	void build(b2World* world, sf::Texture* m_tileset, std::vector<int> tiles,int corridorLength, int corridorWidth);
private:
	const int roomWidth = 15;
	const int roomHeight = 15;
	const int spriteWidth = 2;
	const int spriteHeight = 2;
	const int tileWidth = 3;
	const int tileHeight = 3;
	const int emptyTile = 0;
	TileMap map;
	int x;
	int y;
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	std::vector<Box> boxes;
};

