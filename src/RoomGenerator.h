#pragma once
#include <vector>
#include "Room.h"
#include <utility>
#include <set>
#include <random>
#include <memory>

class RoomGenerator
{
public:
	RoomGenerator() = default;
	std::vector<std::unique_ptr<Room>> generateMap(int nb_rooms) const;
	

};

