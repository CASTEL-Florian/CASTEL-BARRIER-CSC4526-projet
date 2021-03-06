#include "Crate.h"

Crate::Crate(b2World* world, sf::Texture* texture, float scale, const b2Vec2& position)
{
	animator = std::make_unique<Animator>(texture, scale, 32, 32, 0.1f, std::vector<int> {1});
	sf::FloatRect bounds = animator->getLocalBounds();
	w = bounds.width * scale;
	h = bounds.height * scale;
	initBox(world, position, b2_dynamicBody);
}

/**
 * Update the values of the crate.
 *
 * @param elapsed time elapsed since last frame
 */
void Crate::update(sf::Time elapsed) {
	x = body->GetPosition().x;
	y = -body->GetPosition().y;
	rota = -body->GetAngle();
	animator->update(elapsed);
}

/**
 * Display the crate.
 *
 * @param window window in which to render
 */
void Crate::display(sf::RenderWindow& window) const {
	animator->setPosition(sf::Vector2f(x, y));
	animator->setRotation(rota * 180.0f / b2_pi);
	animator->display(window);
}

/**
 * Crate.x getter
 *
 */
float Crate::get_x() const
{
	return x;
}

/**
 * Crate.x getter
 *
 */
float Crate::get_y() const
{
	return y;
}
