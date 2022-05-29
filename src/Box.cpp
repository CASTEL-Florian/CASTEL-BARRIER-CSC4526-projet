#include "Box.h"


void Box::init(b2World* world, const b2Vec2& position, const b2Vec2& dimensions, b2BodyType bodyType) {
	b2BodyDef bodyDef;
	bodyDef.type = bodyType;
	bodyDef.position.Set(position.x, position.y);
	body = world->CreateBody(&bodyDef);
	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimensions.x / 2, dimensions.y / 2);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixture = body->CreateFixture(&fixtureDef);
	x = position.x;
	y = -position.y;
	w = dimensions.x;
	h = dimensions.y;
	rota = 0;
}

void Box::updateSprite() {
	x = body->GetPosition().x;
	y = -body->GetPosition().y;
	rota = -body->GetAngle();
}

void Box::renderRectangle(sf::RenderWindow& window) const {
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2(10 * w, 10 * h));
	rectangle.setOrigin(rectangle.getSize() / 2.f);
	rectangle.setFillColor(sf::Color::Yellow);
	rectangle.setPosition(sf::Vector2(10 * x, 10 * y));
	rectangle.setRotation(rota * 180.0f / b2_pi);
	window.draw(rectangle);
}