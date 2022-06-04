#include "Animator.h"
#include "Animator.h"

Animator::Animator(sf::Texture* textur, const float scal, int spriteWidth, int spriteHeight, float animationTimestep, std::vector<int> imagesNumber) :
	texture(textur), imagesNumber(imagesNumber), spriteWidth(spriteWidth), spriteHeight(spriteHeight), animationTimestep(animationTimestep)
{
	sprite.setTexture(*texture);
	sprite.setScale(sf::Vector2(scal, scal));
	spriteRect.left = 0;
	spriteRect.top = 0;
	spriteRect.width = spriteWidth;
	spriteRect.height = spriteHeight;
	sprite.setTextureRect(spriteRect);
}

void Animator::display(sf::RenderWindow& window) const
{
	window.draw(sprite);
}

void Animator::playAnimation(int id)
{
	animationNumber = id;
	spriteRect.top = id * spriteHeight;
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

void Animator::setScale(sf::Vector2f s)
{
	sprite.setScale(s);
}

sf::FloatRect Animator::getLocalBounds()
{
	return sprite.getLocalBounds();
}

void Animator::setMirrored(bool mirrored)
{
	sf::Vector2f scale = sprite.getScale();
	sprite.setScale(scale.x, mirrored ? -std::abs(scale.y) : std::abs(scale.y));
}

void Animator::update(sf::Time elapsed)
{
	animTimer += elapsed.asSeconds();
	if (animTimer > animationTimestep) {
		spriteRect.left += spriteWidth;
		if (spriteRect.left >= imagesNumber[animationNumber] * spriteWidth)
			spriteRect.left = 0;
		animTimer = 0;
		sprite.setTextureRect(spriteRect);
		
	}
}
