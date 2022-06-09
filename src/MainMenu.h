#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animator.h"
#include "Fader.h"

enum class MainMenuState {Wait, Transition1, Transition2, Transition3, TransitionFinished};

/**
 * Class dealing with everything happening in the main menu.
 */

class MainMenu {
public:
	MainMenu(sf::Texture* backgroundTexture, sf::Texture* playerTexture, Fader* fader, float width, float height);
	void update(sf::Time elapsed);
	void display(sf::RenderWindow& window) const;
	void mousePressed(int x, int y);
	MainMenuState getState() const;
	void updateVolume(sf::Vector2i pos);
	float getUserVolume();
	void setUserVolume(float volume);
private:
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
	const float transitionDuration = 5;
	const float backgroundHeightProportion = 0.5f;
	const float startFadeTime = 4;
	float currentVolume = 1;
	float transitionTime = 0;
	float width;
	float height;
	float userVolume = 1;
	sf::IntRect backgroundSpriteRect;

	std::unique_ptr<sf::Music> sea_ambiant;
	std::unique_ptr<sf::Music> diving_music;

	sf::RectangleShape volumeBar;
	sf::RectangleShape volumeBarWhite;
	sf::FloatRect volumeMouseBox;
	sf::Text volumeText;
	const float volumeBarX = 420;
	const float volumeBarY = 650;
	const float volumeBarWidth = 500;
	const float volumeBarHeight = 10;
};