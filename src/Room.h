#pragma once
#include <utility>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TileMap.h"
#include "Box.h"
#include "Object.h"

const int roomWidth = 31;
const int roomHeight = 31;
const int tileWidth = 3;
const int tileHeight = 3;
const int emptyBackgroundTilePercentage = 85;

class Room
{
public:
	Room(int x, int y);
	void open_path(std::pair<int, int> const& target);
	void display(sf::RenderWindow &window) const;
	void display_fog(sf::RenderWindow &window) const;
	std::pair<int,int> get_position() const;
	bool is_opened(int direction);
	int get_x() const;
	int get_y() const;
	void enter();
	bool isExplored() const;
	bool isDeadEnd() const;
	void linkToRoom(Room* room);
	void build(b2World* world, sf::Texture* m_tileset, std::vector<int> tiles);
	void generateObjects(std::vector<int> const& objects);
	void displayObjects(sf::RenderWindow& window) const;
	void updateObjects(sf::Time elapsed);
	void addObject(std::unique_ptr<Object> object);
	Room* updateCurrentRoom(int roomX, int roomY);
	std::vector<Room*> getAjacentRooms();
	std::vector<std::pair<int, int>> getTreasurePos();
private:
	
	const int spriteWidth = 16;
	const int spriteHeight = 16;
	const int numberOfTilesChoices = 6;
	const int emptyTile = 0;
	TileMap map;
	int x;
	int y;
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	Room* upRoom = nullptr;
	Room* downRoom = nullptr;
	Room* leftRoom = nullptr;
	Room* rightRoom = nullptr;
	bool explored = false;
	sf::VertexArray fogOpen;
	sf::VertexArray fogClose;
	std::vector<sf::Transform> fogTransforms;
	std::vector<std::pair<int, int>> treasurePos;
	std::vector<std::unique_ptr<Object>> objects;
};

