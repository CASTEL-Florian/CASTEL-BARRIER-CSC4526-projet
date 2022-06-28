#include "Game.h"
#include <set>
#include <map>

const int window_length = 1200;
const int window_height = 900;
const int nb_rooms = 20;
const float gravity_down = -3.0f;
const float engine_power = 750.0f;
const float oxygenTime = 60;


Game::Game()
{
	initWindow();
	loadTextures();
	loadMainMenu();
}


/**
 * Update every object that need to be updated and manage transitions between the different states of the game.
 */
void Game::update()
{
	sf::Time elapsed = clock.restart();
	fader->update(elapsed);
	soundHandler->update(elapsed);
	pollEvents();
	if (gameState == GameState::MainMenu) {
		if (mainMenu->getState() == MainMenuState::TransitionFinished) {
			// When the main menu transition is finished, change the game state.
			userVolume = mainMenu->getUserVolume();
			mainMenu.reset();
			gameState = GameState::Playing;
			initGameVariables();
			return;
		}
		mainMenu->update(elapsed);
		return;
	}
	if (gameState == GameState::EndScreen) {
		if (endScreen->getState() == EndScreenState::TransitionFinished) {
			// When the end screen transition is finished, load main menu.
			endScreen.reset();
			resetGame();
			loadMainMenu();
			return;
		}
		endScreen->update(elapsed);
		return;
	}

	// Player is dead or the game is finished. Waiting for the fade out to be finished.
	if (gameState == GameState::TransitionToEndScreen && fader->getState() == FaderState::Sleep) {
		loadEndScreen();
	}
	oxygenBar->update(elapsed);
	world->Step(1.0f / 60.0f, 6, 2); //update box2d physics
	player->update(elapsed);
	player->updateRoomPosition();

	// Update currentRoom in case the player changed room.
	currentRoom = currentRoom->updateCurrentRoom(player->getRoomX(), player->getRoomY());
	currentRoom->enter();
	currentRoom->updateObjects(elapsed);
	currentRoom->updateFog(player->get_x(), player->get_y());

	// Only update the current room and adjacent rooms.
	for (auto& r : currentRoom->getAjacentRooms()) {
		if (r) {
			r->updateObjects(elapsed);
		}
	}
	monster->update(elapsed);
	treasureManager->update(elapsed);
	fishSpawner->update(elapsed);
	bubbleSpawner->update(elapsed);
	minimap->updatePlayerPosition(player->get_x(), player->get_y());
	
	if ((!player->isAlive() || treasureManager->gameWon()) && gameState == GameState::Playing) {
		// The game is finished. Start a fade out and transition before the end screen.
		endType = player->getEndType();
		if (endType == EndType::Drowning) {
			fader->setFadeColor(sf::Color::Blue);
		}
		if (endType == EndType::Victory) {
			fader->setFadeColor(sf::Color::Yellow);
		}
		if (endType == EndType::DeathByMonster) {
			fader->setFadeColor(sf::Color::Red);
		}
		
		fader->fadeOut();
		if (treasureManager->gameWon() || endType == EndType::Drowning)
			soundHandler->switchToCalm();
		gameState = GameState::TransitionToEndScreen;
	}
	view.reset(sf::FloatRect(player->get_x() - window_length / 2, player->get_y() - window_height / 2, window_length, window_height));
	view.zoom(1/10.f);
	
	if (gameState == GameState::Playing)
		time += elapsed.asSeconds();
}

/**
 * Render every object that need to be rendered.
 */
void Game::render() const
{
	window->clear(sf::Color(30, 90, 150));
	if (gameState == GameState::MainMenu) {
		mainMenu->display(*window);
		fader->display(*window);
		window->display();
		return;
	}
	if (gameState == GameState::EndScreen) {
		endScreen->display(*window);
		fader->display(*window);
		window->display();
		return;
	}
	window->setView(view);
	window->draw(depth);
	currentRoom->display(*window);
	currentRoom->displayObjects(*window);

	// Only display the current room and adjacent rooms.
	for (auto& r : currentRoom->getAjacentRooms()) {
		if (r) {
			r->display(*window);
			r->displayObjects(*window);
		}
	}

	bubbleSpawner->display(*window);
	fishSpawner->display(*window);
	monster->display(*window);
	player->display_particles(*window);
	player->renderLight(*window);
	player->display(*window);
	currentRoom->display_fog(*window);
	window->setView(window->getDefaultView());
	minimap->display(*window, rooms);
	oxygenBar->display(*window);
	treasureManager->display(*window);
	fader->display(*window);
	window->display();
}
/**
 * Initialize window and objects active in every game state.
 */
void Game::initWindow()
{
	window = std::make_unique<sf::RenderWindow>(sf::VideoMode(window_length, window_height), "4526 lieues sous les mers");
	window->setFramerateLimit(60);
	fader = std::make_unique<Fader>(window_length, window_height);
	soundHandler = std::make_unique<SoundHandler>();
}

/**
 * Initialize main menu.
 */
void Game::loadMainMenu()
{
	mainMenu = std::make_unique<MainMenu>(&textures[7], &textures[0], fader.get(), window_length, window_height);
	gameState = GameState::MainMenu;
	mainMenu->setUserVolume(userVolume);
	fader->fadeIn();
	clock.restart();
}

/**
 * Initialize end screen.
 */
void Game::loadEndScreen()
{
	// Load a different end screen background depending on the way the game ended.
	if (endType == EndType::DeathByMonster) 
		endScreen = std::make_unique<EndScreen>(&textures, fader.get(), treasureManager.get(), soundHandler.get(), time, window_length, window_height, 8);
	else if (endType == EndType::Drowning) 
		endScreen = std::make_unique<EndScreen>(&textures, fader.get(), treasureManager.get(), soundHandler.get(), time, window_length, window_height, 9);
	else
		endScreen = std::make_unique<EndScreen>(&textures, fader.get(), treasureManager.get(), soundHandler.get(), time, window_length, window_height, 10);
	gameState = GameState::EndScreen;
	fader->fadeIn();
	clock.restart();
}

/**
 * Initialize game variable juste before the player starts playing.
 */
void Game::initGameVariables() {
	minimap = std::make_unique<Minimap>("resources/minimap.png");
	//box2d world
	b2Vec2 gravity(0.0f, gravity_down);
	world = std::make_unique<b2World>(gravity);



	player = std::make_unique<Player>(world.get(), engine_power, &textures[0], &textures[11], 0.2f, soundHandler.get());
	oxygenBar = std::make_unique<OxygenBar>(20, 130, oxygenTime, player.get());
		
	soundHandler->setUserVolume(userVolume);
	soundHandler->playMusic();
	roomGenerator = std::make_unique<RoomGenerator>();
	rooms = roomGenerator->generateMap(nb_rooms);
	rooms = roomGenerator->buildRooms(world.get(), std::move(rooms), &textures);
	currentRoom = rooms[0].get();
	float minX = -tileWidth;
	float maxX = (roomWidth + 1) * tileWidth;
	float minY = -tileHeight;
	float maxY = (roomHeight + 1) * tileHeight;
	for (auto const& room : rooms) {
		float x = (room->get_x() * roomWidth - 1) * tileWidth;
		float y = (room->get_y() * roomHeight - 1) * tileHeight;
		if (x < minX)
			minX = x;
		if (y < minY)
			minY = y;
		x = ((room->get_x() + 1) * roomWidth + 1) * tileWidth;
		y = ((room->get_y() + 1) * roomHeight + 1) *  tileHeight;
		if (x > maxX)
			maxX = x;
		if (y > maxY)
			maxY = y;
	}
	
	depth.setPrimitiveType(sf::Quads);
	depth.resize(4);
	depth[0].position = sf::Vector2f(minX, minY);
	depth[1].position = sf::Vector2f(maxX, minY);
	depth[2].position = sf::Vector2f(maxX, maxY);
	depth[3].position = sf::Vector2f(minX, maxY);
	depth[0].color = sf::Color::Transparent;
	depth[1].color = sf::Color::Transparent;
	depth[2].color = sf::Color::Black;
	depth[3].color = sf::Color::Black;

	monster = std::make_unique<Monster>(player.get(), roomGenerator.get(), &textures[3], 0.2f, soundHandler.get());
	treasureManager = std::make_unique<TreasureManager>(player.get(), &textures[4], &textures[5], soundHandler.get());
	treasureManager->createTreasures(rooms);

	fishSpawner = std::make_unique<FishSpawner>(&textures[6], player.get(), soundHandler.get());
	bubbleSpawner = std::make_unique<BubbleSpawner>(&textures[11], player.get(), oxygenBar.get(), soundHandler.get());
	
	time = 0;
	fader->fadeIn(1);
	clock.restart();
}

/**
 * Load game textures in the textures vector.
 */
void Game::loadTextures()
{
	sf::Texture nauti_texture;//0
	nauti_texture.loadFromFile("resources/nauti_spritesheet.png");
	textures.push_back(nauti_texture);
	sf::Texture crate_texture; //1
	crate_texture.loadFromFile("resources/crate.png");
	textures.push_back(crate_texture);
	sf::Texture crab_texture; //2
	crab_texture.loadFromFile("resources/crab_spritesheet.png");
	textures.push_back(crab_texture);
	sf::Texture monster_texture; //3
	monster_texture.loadFromFile("resources/kalmar_spritesheet.png");
	textures.push_back(monster_texture);
	sf::Texture coin_texture; //4
	coin_texture.loadFromFile("resources/coin_spritesheet.png");
	textures.push_back(coin_texture);
	sf::Texture chest_texture; //5
	chest_texture.loadFromFile("resources/treasure_spritesheet.png");
	textures.push_back(chest_texture); 
	sf::Texture fish_texture; // 6
	fish_texture.loadFromFile("resources/fish_spritesheet.png");
	textures.push_back(fish_texture);
	sf::Texture background_texture; // 7
	background_texture.loadFromFile("resources/background.png");
	textures.push_back(background_texture);
	sf::Texture kalmar_background_texture; // 8
	kalmar_background_texture.loadFromFile("resources/death_kalmar.png");
	textures.push_back(kalmar_background_texture);
	sf::Texture oxygen_background_texture; // 9
	oxygen_background_texture.loadFromFile("resources/death_oxygen.png");
	textures.push_back(oxygen_background_texture);
	sf::Texture victory_background_texture; // 10
	victory_background_texture.loadFromFile("resources/victory_treasure.png");
	textures.push_back(victory_background_texture);
	sf::Texture bubble_texture; // 11
	bubble_texture.loadFromFile("resources/bubble_spritesheet.png");
	textures.push_back(bubble_texture);
}

/**
 * Reset game variables.
 */
void Game::resetGame()
{
	minimap.reset();
	world.reset();
	oxygenBar.reset();
	player.reset();
	soundHandler.reset();
	roomGenerator.reset();
	monster.reset();
	treasureManager.reset();
	fishSpawner.reset();
	soundHandler = std::make_unique<SoundHandler>();
}

/**
 * Check if the window is opened.
 * 
 * @return true if the window is opened, false if the window is closed.
 */
bool Game::running() const {
	return window->isOpen();
}

/**
 * Getting user inputs.
 */
void Game::pollEvents() {
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
		if (event.type == sf::Event::MouseButtonPressed) {
			if (gameState == GameState::MainMenu && event.mouseButton.button == sf::Mouse::Left)
				mainMenu->mousePressed(event.mouseButton.x, event.mouseButton.y);
			if (gameState == GameState::EndScreen && event.mouseButton.button == sf::Mouse::Left)
				endScreen->mousePressed(event.mouseButton.x, event.mouseButton.y);
		}
	}
	if (gameState == GameState::Playing) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) player->move(b2Vec2(0, 1));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) player->move(b2Vec2(0, -1));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) player->move(b2Vec2(1, 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) player->move(b2Vec2(-1, 0));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) player->boost();
	}
	if (gameState == GameState::MainMenu) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			mainMenu->updateVolume(sf::Mouse::getPosition(*window));
		}
	}
}

