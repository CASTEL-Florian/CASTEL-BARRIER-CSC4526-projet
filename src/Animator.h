#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

/**
 * Class that manages a sprite and its animation
 */
class Animator {
public:
	Animator(sf::Texture* textur, const float scal, int spriteWidth, int spriteHeight, float animationTimestep, std::vector<int> imagesNumber);
	void display(sf::RenderWindow& window) const;
	void update(sf::Time elapsed);
	void playAnimation(int id);
	void setOrigin(sf::Vector2f origin);
	void setRotation(float angle);
	void setPosition(sf::Vector2f pos);
	void setScale(sf::Vector2f s);
	sf::FloatRect getLocalBounds();
	void setMirrored(bool mirrored, bool verticalAxis = false, bool bothAxis = false);
private:
	float animTimer = 0;
	sf::Texture* texture;
	sf::Sprite sprite;
	sf::IntRect spriteRect;
	std::vector<int> imagesNumber;
	int spriteWidth;
	int spriteHeight;
	float animationTimestep;
	int animationNumber = 0;
};