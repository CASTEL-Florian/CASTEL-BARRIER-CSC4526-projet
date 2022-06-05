#include "Game.h"
#include <set>
#include <map>

const int window_length = 1200;
const int window_height = 900;
const int nb_rooms = 20;
const float gravity_down = -3.0f;
const float engine_power = 750.0f;


Game::Game()
{
	initVariables();
}



void Game::update()
{
	sf::Time elapsed = clock.restart();
	oxygenBar.update(elapsed);
	pollEvents();
	soundHandler->update(elapsed);
	world->Step(1.0f / 60.0f, 6, 2); //update box2d physics
	for (auto const& o : objects) o->update(elapsed);
	player->update(elapsed);
	player->updateRoomPosition();
	currentRoom = currentRoom->updateCurrentRoom(player->getRoomX(), player->getRoomY());
	currentRoom->enter();
	currentRoom->updateObjects(elapsed);
	for (auto& r : currentRoom->getAjacentRooms()) {
		if (r) {
			r->updateObjects(elapsed);
		}
	}
	monster->update(elapsed);
	treasureManager->update(elapsed);
	fishSpawner->update(elapsed);
	minimap->updatePlayerPosition(player->get_x(), player->get_y());
	view.reset(sf::FloatRect(player->get_x() - window_length / 2, player->get_y() - window_height / 2, window_length, window_height));
	view.zoom(1/10.f);
	window->setView(view);
	
	//std::cout << 1 / elapsed.asSeconds() << " fps" << std::endl;
}

void Game::render() const
{
	window->clear(sf::Color(20, 60, 100));

	currentRoom->display(*window);
	currentRoom->displayObjects(*window);
	for (auto& r : currentRoom->getAjacentRooms()) {
		if (r) {
			r->display(*window);
			r->displayObjects(*window);
		}
	}

	for (auto& o : objects)
		o->display(*window);
	fishSpawner->display(*window);
	monster->display(*window);
	player->renderLight(*window);
	player->display(*window);
	currentRoom->display_fog(*window);
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
	sf::Texture fish_texture;
	fish_texture.loadFromFile("resources/fish_spritesheet.png");
	textures.push_back(fish_texture);

	player = std::make_unique<Player>(world.get(), engine_power, &textures[0], 0.2f);
	
	objects.push_back(std::make_unique<Crab>(world.get(), &textures[2], 0.2f, b2Vec2(roomWidth * tileWidth / 2 + 4 * tileWidth, roomHeight * tileHeight / 2)));
	objects.push_back(std::make_unique<Crab>(world.get(), &textures[2], 0.2f, b2Vec2(roomWidth * tileWidth / 2 + 4 * tileWidth, roomHeight * tileHeight / 2 + tileHeight)));
	objects.push_back(std::make_unique<Crab>(world.get(), &textures[2], 0.2f, b2Vec2(roomWidth * tileWidth / 2 + 4 * tileWidth, roomHeight * tileHeight / 2 + 2 * tileHeight)));
	objects.push_back(std::make_unique<Crab>(world.get(), &textures[2], 0.2f, b2Vec2(roomWidth * tileWidth / 2 + 4 * tileWidth, roomHeight * tileHeight / 2 + 3 * tileHeight)));
	objects.push_back(std::make_unique<Crab>(world.get(), &textures[2], 0.2f, b2Vec2(roomWidth * tileWidth / 2 + 4 * tileWidth, roomHeight * tileHeight / 2 - 3 * tileHeight)));
	objects.push_back(std::make_unique<Crab>(world.get(), &textures[2], 0.2f, b2Vec2(roomWidth * tileWidth / 2 + 4 * tileWidth, roomHeight * tileHeight / 2 - 2 * tileHeight)));
	objects.push_back(std::make_unique<Crab>(world.get(), &textures[2], 0.2f, b2Vec2(roomWidth * tileWidth / 2 + 4 * tileWidth, roomHeight * tileHeight / 2 - tileHeight)));
		

	soundHandler = std::make_unique<SoundHandler>();
	soundHandler->playMusic();

	rooms = roomGenerator.generateMap(nb_rooms);
	rooms = roomGenerator.buildRooms(world.get(), std::move(rooms));
	currentRoom = rooms[0].get();
	monster = std::make_unique<Monster>(player.get(), &roomGenerator, &textures[3], 0.2f, soundHandler.get());
	rooms[0]->addObject(std::make_unique<Crate>(world.get(), &textures[1], 0.2f, b2Vec2(roomWidth* tileWidth / 2 + 2 * tileWidth, roomHeight* tileHeight / 2)));

	treasureManager = std::make_unique<TreasureManager>(player.get(), &roomGenerator, &textures[4], &textures[5]);
	treasureManager->createTreasures(rooms);

	fishSpawner = std::make_unique<FishSpawner>(&textures[6], player.get());
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

