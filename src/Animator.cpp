#include "Animator.h"
#include "Animator.h"

Animator::Animator(sf::Texture* texture, const float scale, int spriteWidth, int spriteHeight, float animationTimestep, std::vector<int> const& imagesNumber) :
	texture(texture), imagesNumber(imagesNumber), spriteWidth(spriteWidth), spriteHeight(spriteHeight), animationTimestep(animationTimestep)
{
	if (!texture)
		return;
	sprite.setTexture(*texture);
	sprite.setScale(sf::Vector2(scale, scale));
	spriteRect.left = 0;
	spriteRect.top = 0;
	spriteRect.width = spriteWidth;
	spriteRect.height = spriteHeight;
	sprite.setTextureRect(spriteRect);
	sprite.setOrigin(sf::Vector2f((float)spriteWidth / 2, (float)spriteHeight / 2));
}

/**
 * Display the sprite on the window.
 *
 * @param window on which the sprite is displayed.
 */
void Animator::display(sf::RenderWindow& window) const
{
	window.draw(sprite);
}

/**
 * Choose the animation to play.
 *
 * @param id index of the animation.
 */
void Animator::playAnimation(int id)
{
	animationNumber = id;
	spriteRect.top = id * spriteHeight;
}

/**
 * Set the origin of the sprite.
 *
 * @param origin of the sprite.
 */
void Animator::setOrigin(sf::Vector2f origin)
{
	sprite.setOrigin(origin);
}

/**
 * Set the rotation of the sprite.
 *
 * @param angle angle of rotation of the sprite.
 */
void Animator::setRotation(float angle)
{
	sprite.setRotation(angle);
}

/**
 * Set the position of the sprite.
 *
 * @param position new position of the sprite.
 */
void Animator::setPosition(sf::Vector2f pos)
{
	sprite.setPosition(pos);
}

/**
 * Set the scale of the sprite.
 *
 * @param scale new scale of the sprite.
 */
void Animator::setScale(sf::Vector2f s)
{
	sprite.setScale(s);
}

void Animator::setColor(sf::Color color)
{
	sprite.setColor(color);
}

/**
 * Set the scale of the sprite.
 *
 * @return sprite local bounds.
 */
sf::FloatRect Animator::getLocalBounds() const
{
	return sprite.getLocalBounds();
}

/**
 * Set the scale of the sprite.
 *
 * @param mirrored whether the sprite should be mirrored or not.
 * @param verticalAxis whether the sprite should be mirrored around the vertical axis.
 * @param verticalAxis whether the sprite should be mirrored around both axis.
 */
void Animator::setMirrored(bool mirrored, bool verticalAxis, bool bothAxis)
{
	sf::Vector2f scale = sprite.getScale();
	if (bothAxis)
	{
		sprite.setScale(mirrored ? -std::abs(scale.x) : std::abs(scale.x), mirrored ? -std::abs(scale.y) : std::abs(scale.y));
		return;
	}
	if (verticalAxis)
		sprite.setScale(mirrored ? -std::abs(scale.x) : std::abs(scale.x), std::abs(scale.y));
	else
		sprite.setScale(std::abs(scale.x), mirrored ? -std::abs(scale.y) : std::abs(scale.y));
}

/**
 * Update the sprite.
 *
 * @param elapsed time spent since last frame.
 */
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
