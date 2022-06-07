#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <Room.h>
#include <RoomGenerator.h>
#include "box2d/box2d.h"
#include "Box.h"
#include "Minimap.h"
#include "Player.h"
#include "OxygenBar.h"
#include "Monster.h"
#include "TreasureManager.h"
#include "Crab.h"
#include "Object.h"
#include "Crate.h"
#include "SoundHandler.h"
#include "FishSpawner.h"
#include "MainMenu.h"
#include "EndScreen.h"


enum class GameState {MainMenu, Playing, EndScreen, TransitionToEndScreen};

class Game
{
public:
	Game();
	void update();
	void render() const;
	bool running() const;
	void pollEvents();
private:
	void initWindow();
	void loadMainMenu();
	void loadEndScreen();
	void initGameVariables();
	void loadTextures();
	void resetGame();
	std::unique_ptr<Fader> fader;
	std::unique_ptr<sf::RenderWindow> window;
	sf::Clock clock;
	sf::Event event;
	std::unique_ptr<RoomGenerator> roomGenerator;
	std::vector<std::unique_ptr<Room>> rooms;
	std::unique_ptr<Minimap> minimap;
	std::unique_ptr<OxygenBar> oxygenBar;

	std::unique_ptr<b2World> world;

	std::vector<std::unique_ptr<Object>> objects;
	std::vector<sf::Texture> textures;

	std::unique_ptr<Player> player;
	std::unique_ptr<Monster> monster;

	std::unique_ptr<TreasureManager> treasureManager;
	std::unique_ptr<SoundHandler> soundHandler;
	std::unique_ptr<FishSpawner> fishSpawner;

	sf::View view;
	sf::VertexArray depth;

	Room* currentRoom;

	std::unique_ptr<MainMenu> mainMenu;
	std::unique_ptr<EndScreen> endScreen;

	GameState gameState = GameState::Playing;
};
