#pragma once
#include "Object.h"
#include "Animator.h"

class Fish :public Object {
public:
	Fish(sf::Texture* texture, float scal, float x, float y);
	void update(sf::Time elapsed) override;
	void display(sf::RenderWindow& window) const override;
	float get_x() const override;
	float get_y() const override;
private:
	std::unique_ptr<Animator> animator;
	float x;
	float y;
};