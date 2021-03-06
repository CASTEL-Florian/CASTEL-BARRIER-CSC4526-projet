#include "OxygenBar.h"

OxygenBar::OxygenBar(float x, float y, float timeMax, Player* player) : timeMax(timeMax), time(timeMax), x(x), y(y), player(player)
{
}

/**
 * Update time value of the oxygen bar and kills player if 0.
 *
 * @param elapsed time elapsed since last frame
 */
void OxygenBar::update(sf::Time elapsed)
{
	if (time >= 0)
		if (player->isBoosting()) {
			time -= elapsed.asSeconds() * boostMultiplier;
		}
		else
			time -= elapsed.asSeconds();
	else {
		time = 0;
		player->kill(EndType::Drowning);
	}
}

/**
 * Display the oxygen bar emptying.
 *
 * @param window window in which to render
 */
void OxygenBar::display(sf::RenderWindow& window) const
{
	sf::RectangleShape rectangle;
	rectangle.setPosition(x, y + height* (1 - (time / timeMax)));
	rectangle.setSize(sf::Vector2f(width, height * time / timeMax));
	rectangle.setFillColor(sf::Color((1 - (time / timeMax)) * 255, 0, (time / timeMax) * 255));

	sf::RectangleShape borders;
	borders.setFillColor(sf::Color::Transparent);
	borders.setOutlineColor(sf::Color::White);
	borders.setOutlineThickness(-1);
	borders.setSize(sf::Vector2f(width, height));
	borders.setPosition(x, y);
	window.draw(rectangle);
	window.draw(borders);

}

void OxygenBar::refill(float amount)
{
	time += amount;
	if (time > timeMax) {
		time = timeMax;
	}
}
