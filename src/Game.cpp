#include "Game.h"
#include <set>
#include <map>

const int window_length = 800;
const int window_height = 600;
const int nb_rooms = 20;
const float gravity_down = -3.0f;
const float engine_power = 100.0f;

const int roomWidth = 15;
const int roomHeight = 15;
const int tileWidth = 3;
const int tileHeight = 3;

Game::Game()
{
	initVariables();
}



void Game::update()
{
	sf::Time elapsed = clock.restart();
	oxygenBar.update(elapsed);
	pollEvents();
	//update box2d physics
	world->Step(1.0f / 60.0f, 6, 2);
	for (auto &b : boxes)
		b.updateSprite();
	player->updateSprite();
	player->updateRoomPosition();
	minimap->updatePlayerPosition(player->get_x(), player->get_y());
	view.reset(sf::FloatRect(player->get_x() - window_length / 2, player->get_y() - window_height / 2, window_length, window_height));
	view.zoom(1/10.f);
	window->setView(view);
	
}

void Game::render() const
{

	window->clear(sf::Color::Blue);
	for (auto& r : rooms) {
		if (r->get_x() == player->getRoomX() && r->get_y() == player->getRoomY())
			r->enter();
		r->display(*window);
	}

	for (auto& b : boxes) {
		//b.renderSprite(*window);
		b.renderRectangle(*window);
	}

	player->renderLight(*window);
	player->renderSprite(*window);
	//player->renderRectangle(*window);

	window->setView(window->getDefaultView());
	minimap->display(*window, rooms);
	oxygenBar.display(*window);
	window->display();
}

void Game::initVariables() {
	
	window = std::make_unique<sf::RenderWindow>(sf::VideoMode(window_length, window_height), "SFML works!");
    window->setFramerateLimit(60);
	minimap = std::make_unique<Minimap>("resources/minimap.png");
	//box2d world
	b2Vec2 gravity(0.0f, gravity_down);
	world = std::make_unique<b2World>(gravity);

	sf::Texture texture_test;
	texture_test.loadFromFile("resources/texture_test.png");

	//testing
	//Box newBox;
	//newBox.init(world.get(), b2Vec2(20,-20), b2_dynamicBody, 1, b2Vec2(10,10));
	//boxes.push_back(newBox);
	//Box newBox2;
	//newBox2.init(world.get(), b2Vec2(27.5f, -17.5f), b2_staticBody, texture_test, 0.2f);
	//boxes.push_back(newBox2);
	//Box newBox4;
	//newBox4.init(world.get(), b2Vec2(23.0f, -25.5f), b2_staticBody, texture_test, 0.2f);
	//boxes.push_back(newBox4);
	
	Player newPlayer{ engine_power };
	newPlayer.init(world.get(), b2Vec2(roomWidth * tileWidth / 2, -roomHeight * tileHeight / 2), b2_dynamicBody, texture_test, 0.02f);
	player = std::make_unique<Player>(newPlayer);
    rooms = roomGenerator.generateMap(world.get(), nb_rooms);
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) player->move(b2Vec2(0, 1));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) player->move(b2Vec2(0, -1));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) player->move(b2Vec2(1, 0));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) player->move(b2Vec2(-1, 0));
}

