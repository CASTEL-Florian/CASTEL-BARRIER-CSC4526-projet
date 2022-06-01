#pragma once
#include <vector>
#include "Room.h"
#include <utility>
#include <set>
#include <random>
#include <memory>
#include "pugixml.hpp"

const std::vector<std::string> roomFiles = { "resources/room1.xml" };
const std::string tileset = "resources/test_tileset.png";
int random_1_to_n(int const nbMax);

class RoomGenerator
{
public:
	RoomGenerator();
	std::vector<std::unique_ptr<Room>> generateMap(b2World* world, int nb_rooms) const;
	
private:
	void buildCorridors();
	const int corridorLength = 1;
	const int corridorWidth = 3;
	std::unique_ptr<sf::Texture> m_tileset;

	std::vector<std::vector<int>> roomTileMaps;

};

