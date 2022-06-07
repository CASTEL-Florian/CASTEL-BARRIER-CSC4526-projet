#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animator.h"
#include "Fader.h"

enum class MainMenuState {Wait, Transition1, Transition2, TransitionFinished};

class MainMenu {
public:
	MainMenu(sf::Texture* backgroundTexture, sf::Texture* playerTexture, Fader* fader, float width, float height);
	void update(sf::Time elapsed);
	void display(sf::RenderWindow& window) const;
	void mousePressed(int x, int y);
	MainMenuState getState() const;
private:
	float easeInOutQuad(float x) const;
	sf::Font font;
	sf::Text gameName;
	sf::Text playText;
	sf::Texture* backgroundTexture;
	std::unique_ptr<Animator> playerAnimator;
	sf::Sprite background;
	Fader* fader;
	MainMenuState state = MainMenuState::Wait;
	float uiAlpha = 255;
	const float uiFadeTime = 1;
	const float playerRoationTime = 5;
	const float backgroundHeightProportion = 0.5f;
	const float startFadeTime = 4;
	float transitionTime = 0;
	float width;
	float height;
	sf::IntRect backgroundSpriteRect;

	std::unique_ptr<sf::Music> sea_ambiant;
	std::unique_ptr<sf::Music> diving_music;
};