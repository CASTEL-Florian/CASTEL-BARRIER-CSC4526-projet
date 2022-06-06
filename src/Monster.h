#pragma once
#include "Player.h"
#include "RoomGenerator.h"
#include "SoundHandler.h"

enum class State{Sleep, Follow, Attack, Flee, PrepareAttack, Explore};

class Monster : public Object{
public:
	Monster(Player* player, RoomGenerator* roomGenerator, sf::Texture* texture, float scale, SoundHandler* soundHandler);
	void display(sf::RenderWindow& window) const override;
	void update(sf::Time elapsed) override;
	float get_x() const override;
	float get_y() const override;
private:
	void rotateToward(float x1, float y1);
	void moveForward();
	float distanceFromPlayer() const;
	std::pair<float,float> getRandomMapPosition();
	void explore();
	void sleep(float duration);
	void dash();
	void follow();
	void flee();
	void prepareAttack();
	float x;
	float y;
	float angle = 0;
	float speed = 10;
	float actionTime = 0;
	float chaseTime = 20;// 10;
	float targetX = 0;
	float targetY = 0;
	float const attackRange = 20;
	float const followSpeed = 13;
	float const dashSpeed = 30;
	float const prepareAttackDuration = 0.3f;// 1.f;
	float const attackDuration = 1;
	float const playerDetectRange = 60;
	State action = State::Sleep;
	Player* player;
	RoomGenerator* roomGenerator;

	std::unique_ptr<Animator> animator;
	SoundHandler* soundHandler;
};