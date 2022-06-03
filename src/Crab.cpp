#include "Crab.h"


void Crab::initSprite(sf::Texture* textur, const float scal) {
	scale = scal;
	texture = textur;
	sf::Sprite newSprite;
	newSprite.setTexture(*texture);
	newSprite.setTextureRect(sf::IntRect(0, 0, 32, 16));
	newSprite.setScale(sf::Vector2f(scale, scale));
	sf::FloatRect bounds = newSprite.getGlobalBounds();
	w = bounds.width;
	h = bounds.height;
}

void Crab::initBox(b2World* world, const b2Vec2& position, b2BodyType bodyType) {
	b2BodyDef bodyDef;
	bodyDef.type = bodyType;
	bodyDef.position.Set(position.x, position.y);
	body = world->CreateBody(&bodyDef);
	b2PolygonShape boxShape;
	boxShape.SetAsBox(w / 2, h / 2);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 0.5f;
	fixtureDef.restitution = 1.f;
	//fixtureDef.friction = 0.3f;
	//body->SetLinearDamping(1);
	//body->SetAngularDamping(2);
	body->SetGravityScale(0);
	fixture = body->CreateFixture(&fixtureDef);
	x = position.x;
	y = -position.y;
	rota = 0;
}

void Crab::update() {
	x = body->GetPosition().x;
	y = -body->GetPosition().y;
	rota = -body->GetAngle();
	animSprite();
}

void Crab::renderSprite(sf::RenderWindow& window) const {
	sf::Sprite sprite;
	sprite.setTexture(*texture);
	sprite.setTextureRect(sf::IntRect(rectOffset, 0, 32, 16));
	sprite.setScale(sf::Vector2f(scale, scale));
	sf::FloatRect bounds = sprite.getLocalBounds();
	float wi = bounds.width;
	float hi = bounds.height;
	sprite.setOrigin(sf::Vector2f(wi, hi) / 2.f);
	sprite.setPosition(sf::Vector2f(x, y));
	sprite.setRotation(rota * 180.0f / b2_pi);
	window.draw(sprite);
}

void Crab::animSprite() {
	if (animTimer.getElapsedTime().asMilliseconds() >= 100) {
		rectOffset += 32;
		if (rectOffset >= 160) {
			rectOffset = 0;
		}
		animTimer.restart();
	}
}