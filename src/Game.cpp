#include "Game.h"
#include <set>
#include <map>


const int window_length = 800;
const int window_height = 600;
const int nb_rooms = 20;
const float gravity_down = -3.0f;

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
	minimap->display(*window, rooms);
	for (auto &r : rooms)
		r->display(*window);
	window->display();
}

void Game::initVariables() {
	window = std::make_unique<sf::RenderWindow>(sf::VideoMode(window_length, window_height), "SFML works!");
    window->setFramerateLimit(60);
    rooms = roomGenerator.generateMap(nb_rooms);
	minimap = std::make_unique<Minimap>("resources/minimap.png");

	//box2d world
	b2Vec2 gravity(0.0f, gravity_down);
	world = std::make_unique<b2World>(gravity);

	//box2d ground for testing
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
	b2Body* groundbody = world->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 0.5f);
	groundbody->CreateFixture(&groundBox, 0.0f);

	Box newBox;
	newBox.init(world.get(), b2Vec2(0.0f, 14.0f), b2Vec2(2.0f, 2.0f));
	boxes.push_back(newBox);
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

