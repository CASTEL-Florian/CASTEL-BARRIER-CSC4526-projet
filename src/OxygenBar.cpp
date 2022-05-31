#include "OxygenBar.h"

OxygenBar::OxygenBar(float x, float y, float timeMax) : timeMax(timeMax), time(timeMax), x(x), y(y)
{
}

void OxygenBar::update(sf::Time elapsed)
{
	time -= elapsed.asSeconds();
}

void OxygenBar::display(sf::RenderWindow& window) const
{
	sf::RectangleShape rectangle;
	rectangle.setPosition(x, y + height* (1 - (time / timeMax)));
	rectangle.setSize(sf::Vector2f(width, height * time / timeMax));
	rectangle.setFillColor(sf::Color::Blue);
	window.draw(rectangle);

}
