#include "Animator.h"

Animator::Animator(sf::Texture* textur, const float scal, int spriteWidth, int spriteHeight, float animationTimestep, std::vector<int> imagesNumber) :
	texture(textur), imagesNumber(imagesNumber), spriteHeight(spriteHeight), scale(scal), animationTimestep(animationTimestep)
{
	sprite.setTexture(*texture);
	spriteRect.left = 0;
	spriteRect.top = 0;
	spriteRect.width = spriteWidth;
	spriteRect.height = spriteHeight;
}

void Animator::display(sf::RenderWindow& window) const
{
	window.draw(sprite);
}

void Animator::playAnimation(int id)
{
	animationNumber = id;
	spriteRect.height = id * spriteHeight;
}

void Animator::setOrigin(sf::Vector2f origin)
{
	sprite.setOrigin(origin);
}

void Animator::setRotation(float angle)
{
	sprite.setRotation(angle);
}

void Animator::setPosition(sf::Vector2f pos)
{
	sprite.setPosition(pos);
}

void Animator::update(sf::Time elapsed)
{
	animTimer += elapsed.asMilliseconds();
	if (animTimer > animationTimestep) {
		spriteRect.left += spriteWidth;
		if (spriteRect.left >= imagesNumber[animationNumber] * spriteWidth)
			spriteRect.left = 0;
		animTimer = 0;
	}
}
