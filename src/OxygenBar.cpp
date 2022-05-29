#include "OxygenBar.h"

OxygenBar::OxygenBar(float x, float y, float timeMax) : x(x), y(y), timeMax(timeMax), time(timeMax)
{
}

void OxygenBar::update(sf::Time elapsed)
{
	time -= elapsed.asSeconds();
}

void OxygenBar::display() const
{
	sf::RectangleShape rectangle;
	rectangle.setPosition(x, y);
}
