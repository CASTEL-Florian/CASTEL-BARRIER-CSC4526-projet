#include "Box.h"

Box::Box() {
}

void Box::init(b2World* world, const b2Vec2& position, const b2Vec2& dimensions) {
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	body = world->CreateBody(&bodyDef);
	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimensions.x / 2, dimensions.y / 2);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixture = body->CreateFixture(&fixtureDef);
	x = position.x - dimensions.x / 2;
	y = position.y - dimensions.y / 2;
	w = dimensions.x;
	h = dimensions.y;
	rota = 0;
}

void Box::updateSprite() {
	x = body->GetPosition().x - w / 2;
	y = -body->GetPosition().y - h / 2;
	rota = body->GetAngle();
	std::cout << "Update - x=" << x << ", y=" << y << std::endl;
}

void Box::render(sf::RenderWindow& window) const {
	sf::RectangleShape rectangle;
	rectangle.setFillColor(sf::Color::Yellow);
	rectangle.setPosition(sf::Vector2(x, y));
	rectangle.setSize(sf::Vector2(w, h));
	rectangle.setRotation(rota);
	window.draw(rectangle);
	std::cout << "Render - x=" << x << ", y=" << y << std::endl;
}