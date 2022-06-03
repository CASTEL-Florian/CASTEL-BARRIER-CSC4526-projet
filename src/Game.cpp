#include "Game.h"
#include <set>
#include <map>

const int window_length = 1200;
const int window_height = 900;
const int nb_rooms = 20;
const float gravity_down = -3.0f;
const float engine_power = 1000.0f;


Game::Game()
{
	initVariables();
}



void Game::update()
{
	sf::Time elapsed = clock.restart();
	oxygenBar.update(elapsed);
	pollEvents();
	world->Step(1.0f / 60.0f, 6, 2); //update box2d physics
	for (auto &b : boxes)
		b->update();
	player->update();
	player->updateRoomPosition();
	monster->update();
	treasureManager->update();
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
		b->renderSprite(*window);
		//b->renderRectangle(*window);
	}
	treasureManager->displayTreasures(*window);
	monster->display(*window);
	player->renderLight(*window);
	player->renderSprite(*window);
	for (auto& r : rooms) {
		if (r->get_x() == player->getRoomX() && r->get_y() == player->getRoomY())
			r->display_fog(*window);
	}
	window->setView(window->getDefaultView());
	minimap->display(*window, rooms);
	oxygenBar.display(*window);
	treasureManager->display(*window);
	window->display();
}

void Game::initVariables() {
	
	window = std::make_unique<sf::RenderWindow>(sf::VideoMode(window_length, window_height), "SFML works!");
    window->setFramerateLimit(60);
	minimap = std::make_unique<Minimap>("resources/minimap.png");
	//box2d world
	b2Vec2 gravity(0.0f, gravity_down);
	world = std::make_unique<b2World>(gravity);

	sf::Texture nauti_texture;
	nauti_texture.loadFromFile("resources/nauti_spritesheet.png");
	textures.push_back(nauti_texture);
	sf::Texture crate_texture;
	crate_texture.loadFromFile("resources/crate.png");
	textures.push_back(crate_texture);
	sf::Texture crab_texture;
	crab_texture.loadFromFile("resources/crab_spritesheet.png");
	textures.push_back(crab_texture);
	sf::Texture monster_texture;
	monster_texture.loadFromFile("resources/kalmar_spritesheet.png");
	textures.push_back(monster_texture);

	Player newPlayer{ engine_power };
	newPlayer.init(world.get(), b2Vec2(roomWidth * tileWidth / 2, -roomHeight * tileHeight / 2), b2_dynamicBody, &textures[0], 0.2f);
	player = std::make_unique<Player>(newPlayer);
	Box crate;
	crate.init(world.get(), b2Vec2(roomWidth * tileWidth / 2 + 2 * tileWidth, -roomHeight * tileHeight / 2), b2_dynamicBody, &textures[1], 0.2f);
	boxes.push_back(std::make_unique<Box>(crate));
	Crab crab;
	crab.init(world.get(), b2Vec2(roomWidth * tileWidth / 2 + 4 * tileWidth, -roomHeight * tileHeight / 2), b2_dynamicBody, &textures[2], 0.2f);
	boxes.push_back(std::make_unique<Crab>(crab));

    rooms = roomGenerator.generateMap(world.get(), nb_rooms);
	monster = std::make_unique<Monster>(player.get(), &roomGenerator, &textures[3]);

	treasureManager = std::make_unique<TreasureManager>(player.get(), &roomGenerator);
	treasureManager->createMainTreasures(rooms);
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

