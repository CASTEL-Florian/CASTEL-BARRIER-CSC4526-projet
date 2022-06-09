#pragma once

#include <SFML/Graphics.hpp>
#include "Animator.h"
class Object
{
public:
	Object() = default;
	virtual void update(sf::Time elapsed) = 0;
	virtual void display(sf::RenderWindow& window) const = 0;
	virtual float get_x() const = 0;
	virtual float get_y() const = 0;
	virtual ~Object() = default;
protected:
	std::unique_ptr<Animator> animator;
};