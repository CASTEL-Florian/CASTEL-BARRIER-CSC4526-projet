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

	window->clear(sf::Color(60, 140, 255));
	sf::Sprite background;
	sf::Texture background_texture;
	background_texture.loadFromFile("resources/background.png");
	background.setTexture(background_texture);
	background.setPosition(-420, -420);
	background.setScale(1.2f, 1.2f);
	window->draw(background);

	for (auto& r : rooms) {
		if (r->get_x() == player->getRoomX() && r->get_y() == player->getRoomY())
			r->enter();
		if (std::abs(r->get_x() - player->getRoomX()) + std::abs(r->get_y() - player->getRoomY()) <= 1)
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
	
	window = std::make_unique<sf::RenderWindow>(sf::VideoMode(window_length, window_height), "4526 lieues sous les mers");
    window->setFramerateLimit(60);
	minimap = std::make_unique<Minimap>("resources/minimap.png");
	//box2d world
	b2Vec2 gravity(0.0f, gravity_down);
	world = std::make_unique<b2World>(gravity);

	sf::Texture nauti_texture;
	nauti_texture.loadFromFile("resources/nauti_spritesheet.png");
	textures.push_back(nauti_texture);
	sf::Texture crate_texture; //0
	crate_texture.loadFromFile("resources/crate.png");
	textures.push_back(crate_texture);
	sf::Texture crab_texture; //1
	crab_texture.loadFromFile("resources/crab_spritesheet.png");
	textures.push_back(crab_texture);
	sf::Texture monster_texture; //2
	monster_texture.loadFromFile("resources/kalmar_spritesheet.png");
	textures.push_back(monster_texture);
	sf::Texture coin_texture; //3
	coin_texture.loadFromFile("resources/coin_spritesheet.png");
	textures.push_back(coin_texture);
	sf::Texture chest_texture; //4
	chest_texture.loadFromFile("resources/treasure_spritesheet.png");
	textures.push_back(chest_texture); //5

	Player newPlayer{ engine_power };
	newPlayer.init(world.get(), b2Vec2(roomWidth * tileWidth / 2, -roomHeight * tileHeight / 2), b2_dynamicBody, &textures[0], 0.2f);
	player = std::make_unique<Player>(newPlayer);
	Box crate;
	crate.init(world.get(), b2Vec2(roomWidth * tileWidth / 2 + 2 * tileWidth, -roomHeight * tileHeight / 2), b2_dynamicBody, &textures[1], 0.2f);
	boxes.push_back(std::make_unique<Box>(crate));
	Crab crab;
	crab.init(world.get(), b2Vec2(roomWidth * tileWidth / 2 + 4 * tileWidth, -roomHeight * tileHeight / 2), b2_dynamicBody, &textures[2], 0.2f);
	boxes.push_back(std::make_unique<Crab>(crab));

	soundHandler = std::make_unique<SoundHandler>();
	soundHandler->playMusic();

    rooms = roomGenerator.generateMap(nb_rooms);
	rooms = roomGenerator.buildRooms(world.get(), std::move(rooms));
	monster = std::make_unique<Monster>(player.get(), &roomGenerator, &textures[3], soundHandler.get());

	treasureManager = std::make_unique<TreasureManager>(player.get(), &roomGenerator, &textures[4], &textures[5]);
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

