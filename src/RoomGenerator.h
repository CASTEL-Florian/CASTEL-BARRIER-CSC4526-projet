#pragma once
#include <vector>
#include "Room.h"
#include <utility>
#include <set>
#include <random>
#include <memory>
#include "pugixml.hpp"

const std::vector<std::string> roomFiles = { "resources/room1.xml", "resources/treasureRoom1.xml" };
const std::string tileset = "resources/room_spritesheet.png";
int random_1_to_n(int const nbMax);

class RoomGenerator
{
public:
	RoomGenerator();
	std::vector<std::unique_ptr<Room>> generateMap(int nb_rooms);
	std::vector<std::unique_ptr<Room>> buildRooms(b2World* world, std::vector<std::unique_ptr<Room>> rooms);
	std::pair<int, int> getFarthestRoomPos() const;
	std::pair<int, int> getRandomRoomPos() const;
	
private:
	const int corridorWidth = 3;
	int treasuresCount = 5;
	std::pair<int, int> farthestRoomPos{ 0,0 };
	std::unique_ptr<sf::Texture> m_tileset;

	std::vector<std::vector<int>> roomTileMaps;
	std::set<std::pair<int, int>> roomPositions;
};

