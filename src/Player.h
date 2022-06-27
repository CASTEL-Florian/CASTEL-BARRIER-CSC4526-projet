#pragma once
#include "Box.h"
#include "Room.h"
#include "Animator.h"
#include "Object.h"
#include "ParticleSystem.h"

enum class EndType {Victory, DeathByMonster, Drowning};

/**
 * Player that can move in every directions with a light at the front.
 */
class Player : public Box, public Object {
public:
	Player(b2World* world, const float enginePower, sf::Texture* texture, sf::Texture* particleTexture, float scale);
	void move(const b2Vec2& vec);
	void boost();
	void update(sf::Time elapsed) override;
	void renderLight(sf::RenderWindow& window) const;
	void display(sf::RenderWindow& window) const override;
	void display_particles(sf::RenderWindow& window) const;
	void updateRoomPosition();
	int getRoomX() const;
	int getRoomY() const;
	float get_x() const override;
	float get_y() const override;
	bool isAlive() const;
	void kill(EndType end);
	EndType getEndType() const;
	bool isBoosting() const;
private:
	float enginePower;
	int roomX = 0;
	int roomY = 0;
	bool alive = true;
	bool boostActive = false;
	EndType endType = EndType::Victory;
	std::unique_ptr<ParticleSystem> particleSystem;
};