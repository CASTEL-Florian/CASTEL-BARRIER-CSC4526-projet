#include "Game.h"
#include <set>
#include <map>

const int window_length = 800;
const int window_height = 600;
const int nb_rooms = 5;
const float gravity_down = -0.3f;
const float engine_power = 10.0f;// 100.0f;

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
	view.reset(sf::FloatRect(player->get_x() - window_length / 2, player->get_y() - window_height / 2, window_length, window_height));
	view.zoom(1/10.f);
	window->setView(view);
	
}

void Game::render() const
{
	window->clear();
	for (auto &r : rooms)
		r->display(*window);

	for (auto& b : boxes)
		b.renderRectangle(*window);

	player->renderRectangle(*window);
	window->setView(window->getDefaultView());
	minimap->display(*window, rooms);
	window->display();
}

void Game::initVariables() {
	
	window = std::make_unique<sf::RenderWindow>(sf::VideoMode(window_length, window_height), "SFML works!");
    window->setFramerateLimit(60);
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
	Box newBox4;
	newBox4.init(world.get(), b2Vec2(23.0f, -25.5f), b2Vec2(2.0f, 4.0f), b2_staticBody);
	boxes.push_back(newBox4);

	Player newPlayer{ engine_power };
	newPlayer.init(world.get(), b2Vec2(25.0f, -15.f), b2Vec2(4.0f, 2.0f), b2_dynamicBody);
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

			/*
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) player->moveUp();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) player->moveDown();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) player->moveRight();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) player->moveLeft();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) player->rotateRight();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) player->rotateLeft();
			*/
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) player->move(b2Vec2(0, 1));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) player->move(b2Vec2(0, -1));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) player->move(b2Vec2(1, 0));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) player->move(b2Vec2(-1, 0));
}

