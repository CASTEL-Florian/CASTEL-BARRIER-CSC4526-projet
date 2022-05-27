#include "Game.h"
#include <set>
#include <map>


const int window_length = 800;
const int window_height = 600;
const int nb_rooms = 20;

Game::Game()
{
	initVariables();
}



void Game::update()
{
	pollEvents();
}

void Game::render() const
{
	window->clear();
	for (auto r : rooms)
		r.display(*window.get());
	window->display();
}

void Game::initVariables() {
	window = std::make_unique<sf::RenderWindow>(sf::VideoMode(window_length, window_height), "SFML works!");
    window->setFramerateLimit(60);
    rooms = roomGenerator.generateMap(nb_rooms);
}

bool Game::running() const {
	return window->isOpen();
}

void Game::pollEvents() {
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}
}

