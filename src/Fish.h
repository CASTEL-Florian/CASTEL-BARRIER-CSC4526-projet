#pragma once
#include "Object.h"
#include "Animator.h"
#include "Player.h"
#include "SoundHandler.h"

class FishSpawner;

enum class FishAction {Stop, MoveLeft, MoveRight, Flee};

class Fish :public Object {
public:
	Fish(sf::Texture* texture, FishSpawner* fishSpawner, Player* player, float scale, float x, float y, SoundHandler* soundHandler);
	void update(sf::Time elapsed) override;
	void display(sf::RenderWindow& window) const override;
	float get_x() const override;
	float get_y() const override;
	void init(float posX, float posY);
private:
	std::unique_ptr<Animator> animator;
	float distanceFromPlayer() const;
	void rotateToward(float x1, float y1);
	float x;
	float y;
	FishSpawner* fishSpawner;
	Player* player;
	FishAction action = FishAction::Stop;
	const float acceleration = 0.1f;
	const float maxSpeed = 5;
	const float fleeSpeed = 20;
	const float actionDuration = 3;
	const float fleeDistance = 20;
	const float despawnDistance = 100;
	float actionTime = 0;
	float speed = 0;
	float angle = 0;
	SoundHandler* soundHandler;
};