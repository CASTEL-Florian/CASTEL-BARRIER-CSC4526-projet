#pragma once
#include "Fish.h"

class FishSpawner {
public:
	FishSpawner();
private:
	std::vector<std::unique_ptr<Fish>> fishVector;
};