#include "Game.h"
#include <set>
#include <map>

const int window_length = 800;
const int window_height = 600;
const int nb_rooms = 20;
const float gravity_down = -30.0f;

Game::Game()
{
	initVariables();
}



void Game::update()
{
	pollEvents();

	//update box2d physics
	world->Step(1.0f / 60.0f, 6, 2);
	for (auto &b : boxes)
		b.updateSprite();
}

void Game::render() const
{
	window->clear();
	for (auto r : rooms)
		r.display(*window.get());
	for (auto& b : boxes)
		b.render(*window.get());
	window->display();
}

void Game::initVariables() {
	window = std::make_unique<sf::RenderWindow>(sf::VideoMode(window_length, window_height), "SFML works!");
    window->setFramerateLimit(60);
    rooms = roomGenerator.generateMap(nb_rooms);

	//box2d world
	b2Vec2 gravity(0.0f, gravity_down);
	world = std::make_unique<b2World>(gravity);

	
	//box2d ground for testing
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, 0.0f);
	b2Body* groundbody = world->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(500.0f, 1.0f, b2Vec2(500.0f, 1.0f), 10.0f);
	groundbody->CreateFixture(&groundBox, 0.0f);
	

	Box newBox;
	newBox.init(world.get(), b2Vec2(50.0f, 50.0f), b2Vec2(20.0f, 40.0f));
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

