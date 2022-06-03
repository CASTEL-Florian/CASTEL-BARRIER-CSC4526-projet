#pragma once
#include "Player.h"
#include "RoomGenerator.h"
enum class State{Sleep, Follow, Attack, Flee, PrepareAttack, Explore};

class Monster {
public:
	Monster(Player* player, RoomGenerator* roomGenerator);
	void display(sf::RenderWindow& window) const;
	void update();
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
	float chaseTime = 10;
	float targetX = 0;
	float targetY = 0;;
	float const attackRange = 20;
	float const followSpeed = 13;
	float const dashSpeed = 30;
	float const prepareAttackDuration = 1.f;
	float const attackDuration = 1;
	float const playerDetectRange = 60;
	State action = State::Sleep;
	Player* player;
	RoomGenerator* roomGenerator;
};