#pragma once
#include <utility>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <Room.h>

class Game
{
public:
	Game();
	void update();
	void render() const;
	bool running() const;
	void pollEvents();
private:
	void generateMap();
	void initVariables();
	std::unique_ptr<sf::RenderWindow> window;
	sf::Event event;
	std::vector<Room> rooms;

};
