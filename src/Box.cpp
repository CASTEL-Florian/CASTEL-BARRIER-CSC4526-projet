#include "Box.h"
#include "Box.h"
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
	fixtureDef.density = 0.1f;// 1.0f;
	fixtureDef.friction = 0.3f;
	body->SetLinearDamping(1);
	body->SetAngularDamping(2);
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
	rectangle.setSize(sf::Vector2(1 * w, 1 * h));
	rectangle.setOrigin(rectangle.getSize() / 2.f);
	rectangle.setFillColor(sf::Color::Yellow);
	rectangle.setPosition(sf::Vector2(1 * x, 1 * y));
	rectangle.setRotation(rota * 180.0f / b2_pi);
	window.draw(rectangle);
}

float Box::get_x() const
{
	return x;
}

float Box::get_y() const
{
	return y;
}
