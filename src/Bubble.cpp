#include "Bubble.h"

Bubble::Bubble(sf::Texture* texture, Player* player, OxygenBar* oxygenBar, SoundHandler* soundHandler) : 
	player(player), oxygenBar(oxygenBar), soundHandler(soundHandler)
{
	animator = std::make_unique<Animator>(texture, 0.25f, 16, 16, 0.1f, std::vector<int> {8});
}

void Bubble::update(sf::Time elapsed)
{
	if (!alive)
		return;
	y -= speed * elapsed.asSeconds();
	time += elapsed.asSeconds();
	animator->update(elapsed);
	if (time > lifetime) {
		alive = false;
		return;
	}
	if (distanceFromPlayer() < playerCatchRange) {
		alive = false;
		oxygenBar->refill(oxygenAmount);
		soundHandler->playBubbleSound();
	}
}

void Bubble::display(sf::RenderWindow& window) const
{
	animator->setPosition(sf::Vector2f(x, y));
	animator->setColor(sf::Color(255, 255, 255, 255 * alphaFromLifetime(time)));
	animator->display(window);
}

float Bubble::get_x() const
{
	return x;
}

float Bubble::get_y() const
{
	return y;
}

void Bubble::init(float x_, float y_)
{
	x = x_;
	y = y_;
	alive = true;
	time = 0;
}

bool Bubble::isAlive() const
{
	return alive;
}

float Bubble::alphaFromLifetime(float t) const
{
	if (t < fadeTime) {
		float value = 1 - (t / fadeTime);
		return 1 - value * value * value * value;
	}
	if (t > lifetime - fadeTime) {
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
