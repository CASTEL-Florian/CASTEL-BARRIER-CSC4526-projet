#include "Bubble.h"

Bubble::Bubble(sf::Texture* texture, Player* player, OxygenBar* oxygenBar, SoundHandler* soundHandler) : 
	player(player), oxygenBar(oxygenBar), soundHandler(soundHandler)
{
	animator = std::make_unique<Animator>(texture, 0.25f, 16, 16, 0.1f, std::vector<int> {8});
}

/**
 * Update the bubble.
 *
 * @param elapsed time since last frame.
 */
void Bubble::update(sf::Time elapsed)
{
	if (!alive)
		return;
	y -= speed * elapsed.asSeconds();  // The bubble goes up slowly.
	time += elapsed.asSeconds();
	animator->update(elapsed);
	if (time > lifetime) {
		alive = false;
		return;
	}

	// Collect the bubble if it is close enough to the player. 
	if (distanceFromPlayer() < playerCatchRange) {
		alive = false;
		oxygenBar->refill(oxygenAmount);
		soundHandler->playBubbleSound();
	}
}

/**
 * Display the bubble on the window.
 *
 * @param window on which the bubble is drawn.
 */
void Bubble::display(sf::RenderWindow& window) const
{
	animator->setPosition(sf::Vector2f(x, y));
	animator->setColor(sf::Color(255, 255, 255, 255 * alphaFromLifetime(time)));
	animator->display(window);
}

/**
 * Bubble.x getter
 *
 */
float Bubble::get_x() const
{
	return x;
}

/**
 * Bubble.y getter
 *
 */
float Bubble::get_y() const
{
	return y;
}

/**
 * Initialize the position of the bubble.
 *
 * @param posX x position of the bubble.
 * @param posY y position of the bubble.
 */
void Bubble::init(float x_, float y_)
{
	x = x_;
	y = y_;
	alive = true;
	time = 0;
}

/**
 * Bubble.alive getter
 *
 */
bool Bubble::isAlive() const
{
	return alive;
}


/**
 * Calculate the alpha of the bubble depending on it's lifetime.
 *
 * @param lifetime of the bubble.
 */
float Bubble::alphaFromLifetime(float t) const
{
	if (t < fadeTime) {
		// Fade in.
		float value = 1 - (t / fadeTime);
		return 1 - value * value * value * value;
	}
	if (t > lifetime - fadeTime) {
		// Fade out.
		float value = (t + fadeTime - lifetime) / fadeTime;
		return 1 - value * value * value * value;
	}
	return 1;
}

float Bubble::distanceFromPlayer() const
{
	sf::Vector2f dir(player->get_x() - x, player->get_y() - y);
	return std::sqrt(dir.x * dir.x + dir.y * dir.y);
}
