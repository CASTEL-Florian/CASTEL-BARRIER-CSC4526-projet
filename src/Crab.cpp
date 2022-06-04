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
	//fixtureDef.friction = 0.3f;
	//body->SetLinearDamping(1);
	//body->SetAngularDamping(2);
	body->SetGravityScale(0);
	fixture = body->CreateFixture(&fixtureDef);
	x = position.x;
	y = position.y;
	rota = 0;
}

void Crab::update(sf::Time elapsed) {
	x = body->GetPosition().x;
	y = -body->GetPosition().y;
	rota = -body->GetAngle();
	animator->update(elapsed);
}

void Crab::display(sf::RenderWindow& window) const {
	animator->setPosition(sf::Vector2f(x, y));
	animator->setRotation(rota * 180.0f / b2_pi);
	animator->display(window);
}
