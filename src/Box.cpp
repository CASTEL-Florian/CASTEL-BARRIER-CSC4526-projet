#include "Box.h"

void Box::init(b2World* world, const b2Vec2& position, b2BodyType bodyType, sf::Texture& textur, const float scal) {
	initSprite(textur, scal);
	initBox(world, position, bodyType);
}

void Box::initSprite(sf::Texture& textur, const float scal) {
	scale = scal;
	texture = textur;
	sf::Sprite newSprite;
	newSprite.setTexture(texture);
	newSprite.setScale(sf::Vector2f(scale, scale));
	sf::FloatRect bounds = newSprite.getGlobalBounds();
	w = bounds.width / 10;
	h = bounds.height / 10;
}

void Box::initBox(b2World* world, const b2Vec2& position, b2BodyType bodyType) {
	b2BodyDef bodyDef;
	bodyDef.type = bodyType;
	bodyDef.position.Set(position.x, position.y);
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
	y = -position.y;
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

void Box::renderSprite(sf::RenderWindow& window) const {
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(scale, scale));
	sf::FloatRect bounds = sprite.getLocalBounds();
	float wi = bounds.width;
	float hi = bounds.height;
	sprite.setOrigin(sf::Vector2f(wi, hi) / 2.f);
	sprite.setPosition(sf::Vector2f(10 * x, 10 * y));
	sprite.setRotation(rota * 180.0f / b2_pi);
	window.draw(sprite);
}