#include "Box.h"


void Box::init(b2World* world, const b2Vec2& position, const b2Vec2& dimensions, const float density) {
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	body = world->CreateBody(&bodyDef);
	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimensions.x / 2, dimensions.y / 2);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = density;
	fixtureDef.friction = 0.3f;
	fixture = body->CreateFixture(&fixtureDef);
	x = position.x - dimensions.x / 2;
	y = -position.y - dimensions.y / 2;
	w = dimensions.x;
	h = dimensions.y;
	rota = 0;
}

void Box::updateSprite() {
	x = body->GetPosition().x -w / 2;
	y = -body->GetPosition().y -h / 2;
	rota = -body->GetAngle();
}

void Box::render(sf::RenderWindow& window) const {
	sf::RectangleShape rectangle;
	rectangle.setFillColor(sf::Color::Yellow);
	rectangle.setPosition(sf::Vector2(10 * x, 10 * y));
	rectangle.setSize(sf::Vector2(10 * w, 10 * h));
	rectangle.setRotation(rota * 180.0 / b2_pi / 4);
	window.draw(rectangle);
}