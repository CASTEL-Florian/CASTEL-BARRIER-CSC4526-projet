#pragma once
#include <vector>
#include "Room.h"
#include <utility>
#include <set>
#include <random>
#include <memory>
#include "pugixml.hpp"

const std::string emptyRoomFile = "resources/emptyRoom.xml";
const std::vector<std::string> treasureRoomFiles = { "resources/treasureRoom1.xml", "resources/treasureRoom2.xml" };
const std::vector<std::string> standardRoomFiles = { "resources/standardRoom1.xml", "resources/standardRoom2.xml" , "resources/standardRoom3.xml" , "resources/standardRoom4.xml" , "resources/standardRoom5.xml" , "resources/standardRoom6.xml" , "resources/crabRoom.xml" , "resources/crateRoom.xml"};
const std::string tileset = "resources/room_spritesheet.png";
int random_1_to_n(int const nbMax);
const int corridorWidth = 5;
const float emptyRoomProportion = 0.1f; //0.5f

/**
 * Class that generate the map.
 */
class RoomGenerator
{
public:
	RoomGenerator();
	std::vector<std::unique_ptr<Room>> generateMap(int nb_rooms);
	std::vector<std::unique_ptr<Room>> buildRooms(b2World* world, std::vector<std::unique_ptr<Room>> rooms, std::vector<sf::Texture>* textures);
	std::pair<int, int> getFarthestRoomPos() const;
	std::pair<int, int> getRandomRoomPos() const;
private:
	std::vector<int> loadXMLroom(std::string const& file) const;
	std::pair<int, int> farthestRoomPos{ 0,0 };
	std::unique_ptr<sf::Texture> m_tileset;

	std::vector<int> emptyRoomTilemap;
	std::vector<std::vector<int>> treasureRoomTilemaps;
	std::vector<std::vector<int>> standardRoomTilemaps;
	std::set<std::pair<int, int>> roomPositions;
};

