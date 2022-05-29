#include "Game.h"
#include <set>
#include <map>

const int window_length = 800;
const int window_height = 600;
const int nb_rooms = 20;
const float gravity_down = -0.3f;
const float engine_power = 100.0f;

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
	player->updateSprite();
}

void Game::render() const
{

	window->clear();
	//minimap->display(*window, rooms);
	//for (auto &r : rooms)
	//	r->display(*window);

	for (auto& b : boxes)
		b.renderRectangle(*window);

	player->renderRectangle(*window);

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

	//testing
	Box newBox;
	newBox.init(world.get(), b2Vec2(25.0f, -2.50f), b2Vec2(4.0f, 2.0f), b2_dynamicBody);
	boxes.push_back(newBox);
	Box newBox2;
	newBox2.init(world.get(), b2Vec2(27.5f, -17.5f), b2Vec2(2.0f, 4.0f), b2_staticBody);
	boxes.push_back(newBox2);
	Box newBox3; //ground
	newBox3.init(world.get(), b2Vec2(0.0f, -40.0f), b2Vec2(200.0f, 2.0f),  b2_staticBody);
	boxes.push_back(newBox3);
	Box newBox4;
	newBox4.init(world.get(), b2Vec2(23.0f, -25.5f), b2Vec2(2.0f, 4.0f), b2_staticBody);
	boxes.push_back(newBox4);

	Player newPlayer{ engine_power };
	newPlayer.init(world.get(), b2Vec2(50.0f, -2.50f), b2Vec2(4.0f, 2.0f), b2_dynamicBody);
	player = std::make_unique<Player>(newPlayer);
}

bool Game::running() const {
	return window->isOpen();
}

void Game::pollEvents() {
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
		if (event.type == sf::Event::KeyPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) player->moveUp();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) player->moveDown();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) player->moveRight();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) player->moveLeft();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) player->rotateRight();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) player->rotateLeft();
		}
	}
}

