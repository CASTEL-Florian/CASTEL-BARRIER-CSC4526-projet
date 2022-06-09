#include "Box.h"

/**
 * Initialize the box with dimensions, calling initializer initBox.
 *
 * @param world b2World in which physical interactions take place
 * @param position position of the box in the b2World
 * @param bodyType type of the bodyDef (static of dynamic)
 * @param dimensions dimensions of the box
 */
void Box::init(b2World* world, const b2Vec2& position, b2BodyType bodyType, const b2Vec2& dimensions)
{
	w = dimensions.x;
	h = dimensions.y;
	initBox(world, position, bodyType);
}

/**
 * Initialize the box2d box.
 *
 * @param world b2World in which physical interactions take place
 * @param position position of the box in the b2World
 * @param bodyType type of the bodyDef (static of dynamic)
 */
void Box::initBox(b2World* world, const b2Vec2& position, b2BodyType bodyType) {
	b2BodyDef bodyDef;
	bodyDef.type = bodyType;
	bodyDef.position.Set(position.x, -position.y);
	body = world->CreateBody(&bodyDef);
	b2PolygonShape boxShape;
	boxShape.SetAsBox(w / 2, h / 2);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 0.5f;
	fixtureDef.friction = 0.3f;
	body->SetLinearDamping(1);
	body->SetAngularDamping(2);
	fixture = body->CreateFixture(&fixtureDef);
	x = position.x;
	y = position.y;
	rota = 0;
}

/**
 * Update the values of the box.
 *
 * @param elapsed time elapsed since last frame
 */
void Box::update(sf::Time elapsed) {
	x = body->GetPosition().x;
	y = -body->GetPosition().y;
	rota = -body->GetAngle();
}

/**
 * Render the box as a colored rectangle.
 *
 * @param window window in which the box is rendered
 */
void Box::renderRectangle(sf::RenderWindow& window) const {
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2(1 * w, 1 * h));
	rectangle.setOrigin(rectangle.getSize() / 2.f);
	rectangle.setFillColor(sf::Color::Yellow);
	rectangle.setPosition(sf::Vector2(1 * x, 1 * y));
	rectangle.setRotation(rota * 180.0f / b2_pi);
	window.draw(rectangle);
}

