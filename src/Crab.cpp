#include "Crab.h"


Crab::Crab(b2World* world, sf::Texture* texture, float scal, const b2Vec2& position)
{
	animator = std::make_unique<Animator>(texture,scal,32,16, 0.1f,std::vector<int> {6});
	sf::FloatRect bounds = animator->getLocalBounds();
	w = bounds.width * scal;
	h = bounds.height * scal;
	initCrabBox(world, position, b2_dynamicBody);
	animator->setOrigin(sf::Vector2f(w / scal, h / scal) / 2.f);
}

/**
 * Initialize the crab in the b2World.
 *
 * @param world b2World in which physical interactions take place
 * @param position position of the crab in the b2World
 * @param bodyType type of the bodyDef (static of dynamic)
 */
void Crab::initCrabBox(b2World* world, const b2Vec2& position, b2BodyType bodyType) {
	b2BodyDef bodyDef;
	bodyDef.type = bodyType;
	bodyDef.position.Set(position.x, -position.y);
	body = world->CreateBody(&bodyDef);
	b2PolygonShape boxShape;
	boxShape.SetAsBox(w / 2, h / 2);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 0.5f;
	fixtureDef.restitution = 1.f;
	body->SetGravityScale(0);
	fixture = body->CreateFixture(&fixtureDef);
	x = position.x;
	y = position.y;
	rota = 0;
}

/**
 * Update the values of the crab.
 *
 * @param elapsed time elapsed since last frame
 */
void Crab::update(sf::Time elapsed) {
	x = body->GetPosition().x;
	y = -body->GetPosition().y;
	rota = -body->GetAngle();
	animator->update(elapsed);
}

/**
 * Display the crab.
 *
 * @param window window in which to render
 */
void Crab::display(sf::RenderWindow& window) const {
	animator->setPosition(sf::Vector2f(x, y));
	animator->setRotation(rota * 180.0f / b2_pi);
	animator->display(window);
}

/**
 * Crab.x getter
 *
 */
float Crab::get_x() const
{
	return x;
}

/**
 * Crab.y getter
 *
 */
float Crab::get_y() const
{
	return y;
}
