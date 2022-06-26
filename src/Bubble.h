#pragma once
#include "Object.h"
#include "Player.h"
#include "OxygenBar.h"

/**
 * Solid crab bouncing on everything.
 */
class Bubble : public Object {
public:
	Bubble(sf::Texture* texture, Player* player, OxygenBar* oxygenBar);
	void update(sf::Time elapsed) override;
	void display(sf::RenderWindow& window) const override;
	float get_x() const override;
	float get_y() const override;
	void init(float x, float y);
	bool isAlive() const;
private:
	float alphaFromLifetime(float x) const;
	float x;
	float y;
	const float speed = 1.f;
	const float playerCatchRange = 7;
	const float lifetime = 10.f;
	const float fadeTime = 1.f;
	const float oxygenAmount = 15.f;
	float time = 0;
	bool alive = true;
	float distanceFromPlayer() const;
	Player* player;
	OxygenBar* oxygenBar;
};