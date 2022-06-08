#pragma once
#include <SFML/Graphics.hpp>
#include "Fader.h"
#include "Animator.h"
#include "TreasureManager.h"
#include "SoundHandler.h"

enum class EndScreenState {Wait, Transition, TransitionFinished};

class EndScreen {
public:
	EndScreen(sf::Texture* backgroundTexture, sf::Texture* coinTexture, sf::Texture* treasureTexture, Fader* fader, const TreasureManager* treasureManager, SoundHandler* soundHandler, float width, float height);
	void update(sf::Time elapsed);
	void display(sf::RenderWindow& window) const;
	void mousePressed(int x, int y);
	EndScreenState getState() const;
private:
	sf::Font font;
	sf::Text coinText;
	sf::Text treasureText;
	sf::Text returnText;
	Fader* fader;
	SoundHandler* soundHandler;
	sf::Texture* backgroundTexture;
	std::unique_ptr<Animator> coinAnimator;
	std::unique_ptr<Animator> treasureAnimator;;
	float width;
	float height;
	EndScreenState state = EndScreenState::Wait;
	sf::Sprite background;
};