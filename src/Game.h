#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <Room.h>
#include <RoomGenerator.h>

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
	sf::Event event;
	RoomGenerator roomGenerator;
	std::vector<Room> rooms;

};
