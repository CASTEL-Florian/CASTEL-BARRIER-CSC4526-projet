#include "Box.h"
#include "Box.h"


void Box::init(b2World* world, const b2Vec2& position, b2BodyType bodyType, const b2Vec2& dimensions)
{
	w = dimensions.x;
	h = dimensions.y;
	initBox(world, position, bodyType);
}


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

void Box::update(sf::Time elapsed) {
	x = body->GetPosition().x;
	y = -body->GetPosition().y;
	rota = -body->GetAngle();
}

void Box::renderRectangle(sf::RenderWindow& window) const {
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2(1 * w, 1 * h));
	rectangle.setOrigin(rectangle.getSize() / 2.f);
	rectangle.setFillColor(sf::Color::Yellow);
	rectangle.setPosition(sf::Vector2(1 * x, 1 * y));
	rectangle.setRotation(rota * 180.0f / b2_pi);
	window.draw(rectangle);
}

