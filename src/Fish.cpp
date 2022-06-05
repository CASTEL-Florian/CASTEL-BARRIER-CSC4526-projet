#include "Fish.h"

Fish::Fish(sf::Texture* texture, float scal, float x, float y) : x(x), y(y)
{
	
}

void Fish::update(sf::Time elapsed)
{
}

void Fish::display(sf::RenderWindow& window) const
{
	sf::RectangleShape rect;
	rect.setFillColor(sf::Color::Magenta);
	rect.setSize(sf::Vector2f(5, 2));
	rect.setOrigin(rect.getSize() / 2.f);
	rect.setPosition(x, y);
	window.draw(rect);
}

float Fish::get_x() const
{
	return x;
}

float Fish::get_y() const
{
	return y;
}
