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
const int emptyBackgroundTilePercentage = 15;

/**
 * Class representing a room.
 */
class Room
{
public:
	Room(int x, int y);
	void open_path(std::pair<int, int> const& target);
	void display(sf::RenderWindow &window) const;
	void updateFog(float px, float py);
	void display_fog(sf::RenderWindow &window) const;
	std::pair<int,int> get_position() const;
	bool is_opened(int direction) const;
	int get_x() const;
	int get_y() const;
	void enter();
	bool isExplored() const;
	bool isDeadEnd() const;
	void linkToRoom(Room* room);
	void build(b2World* world, sf::Texture* m_tileset, std::vector<int> tiles, std::vector<int> objects);
	void generateObjects(b2World* world, std::vector<int> const& objects, std::vector<sf::Texture>* textures);
	void displayObjects(sf::RenderWindow& window) const;
	void updateObjects(sf::Time elapsed);
	void addObject(std::unique_ptr<Object> object);
	std::vector<std::unique_ptr<Object>>* getObjects();
	Room* updateCurrentRoom(int roomX, int roomY);
	std::vector<Room*> getAjacentRooms();
	std::vector<std::pair<float, float>> getTreasurePos() const;
	std::pair<float,float> findAvailableCoinPosition();
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
	sf::VertexArray fogOpenL; // Fog to display on the sides that are open.
	sf::VertexArray fogOpenD; 
	sf::VertexArray fogOpenR; 
	sf::VertexArray fogOpenU; 
	sf::VertexArray fogClose; // Fog to display on the sides that are close.
	std::vector<sf::Transform> fogTransforms;
	std::vector<std::pair<float, float>> treasurePos;
	std::vector<std::unique_ptr<Object>> objects;
	std::vector<int> objectsTilemap;
};

