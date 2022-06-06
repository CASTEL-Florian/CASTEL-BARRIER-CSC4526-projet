#pragma once
#include <SFML/Graphics.hpp>
#include "Fader.h"
#include "Animator.h"

class EndScreen {
public:
	EndScreen(sf::Texture* backgroundTexture, sf::Texture* coinTexture, sf::Texture* treasureTexture, Fader* fader, float width, float height);
	void update(sf::Time elapsed);
	void display(sf::RenderWindow& window) const;
	void mousePressed(int x, int y);
private:
	sf::Font font;
	sf::Text coinText;
	sf::Text treasureText;
	sf::Text returnText;
	Fader* fader;
	sf::Texture* backgroundTexture;
	std::unique_ptr<Animator> coinAnimator;
	std::unique_ptr<Animator> treasureAnimator;;
	float width;
	float height;
	sf::IntRect backgroundSpriteRect;
};