#pragma once
#include <SFML/Graphics.hpp>
#include "Fader.h"
#include "Animator.h"
#include "TreasureManager.h"
#include "SoundHandler.h"

/**
 * The different states of the end screen.
 */
enum class EndScreenState {Wait, Transition, TransitionFinished};

/**
 * Class dealing with everything happening in the end screen.
 */
class EndScreen {
public:
	EndScreen(std::vector<sf::Texture>* textures, Fader* fader, const TreasureManager* treasureManager, SoundHandler* soundHandler, float time, float width, float height, int backgroundId);
	void update(sf::Time elapsed);
	void display(sf::RenderWindow& window) const;
	void mousePressed(int x, int y);
	EndScreenState getState() const;
private:
	sf::Font font;
	sf::Text coinText;
	sf::Text treasureText;
	sf::Text returnText;
	sf::Text timeText;
	sf::Text scoreText;
	Fader* fader;
	SoundHandler* soundHandler;
	sf::Texture* backgroundTexture;
	std::unique_ptr<Animator> coinAnimator;
	std::unique_ptr<Animator> treasureAnimator;;
	float width;
	float height;
	EndScreenState state = EndScreenState::Wait;
	sf::Sprite background;

	const int treasureScore = 500;
	const int coinScore = 100;
	const int timeScore = 2000;
	const float timeScoreDecreaseSpeed = 0.006f;
};