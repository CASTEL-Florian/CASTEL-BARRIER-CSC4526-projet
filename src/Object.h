#pragma once

#include <SFML/Graphics.hpp>
class Object
{
public:
	Object() = default;
	virtual void update(sf::Time elapsed) = 0;
	virtual void display(sf::RenderWindow& window) const = 0;
	virtual ~Object() = default;
};