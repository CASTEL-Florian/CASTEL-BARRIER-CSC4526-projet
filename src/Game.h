#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <Room.h>
#include <RoomGenerator.h>
#include "box2d/box2d.h"
#include "Box.h"
#include "Minimap.h"
#include "Player.h"
#include "OxygenBar.h"
#include "Monster.h"
#include "TreasureManager.h"
#include "Crab.h"
#include "Object.h"
#include "Crate.h"


class Game
{
public:
	Game();
	void update();
	void render() const;
	bool running() const;
	void pollEvents();
private:
	void initVariables();
	std::unique_ptr<sf::RenderWindow> window;
	sf::Clock clock;
	sf::Event event;
	RoomGenerator roomGenerator;
	std::vector<std::unique_ptr<Room>> rooms;
	std::unique_ptr<Minimap> minimap;
	OxygenBar oxygenBar{ 20,130,30 };

	std::unique_ptr<b2World> world;

	std::vector<std::unique_ptr<Object>> objects;
	std::vector<sf::Texture> textures;

	std::unique_ptr<Player> player;
	std::unique_ptr<Monster> monster;

	std::unique_ptr<TreasureManager> treasureManager;

	sf::View view;
};
