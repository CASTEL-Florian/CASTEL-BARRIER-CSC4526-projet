#pragma once
#include <SFML/Graphics.hpp>

class Animator {
public:
	Animator(sf::Texture* textur, const float scal, int spriteWidth, int spriteHeight, float animationTimestep, std::vector<int> imagesNumber);
	void display(sf::RenderWindow& window) const;
	void update(sf::Time elapsed);
	void playAnimation(int id);
	void setOrigin(sf::Vector2f origin);
	void setRotation(float angle);
	void setPosition(sf::Vector2f pos);
private:
	float animTimer;
	sf::Texture* texture;
	sf::Sprite sprite;
	sf::IntRect spriteRect;
	std::vector<int> imagesNumber;
	int spriteWidth;
	int spriteHeight;
	float scale;
	float animationTimestep;
	int animationNumber = 0;
};