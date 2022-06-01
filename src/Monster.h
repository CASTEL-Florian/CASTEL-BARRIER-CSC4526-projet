#include "Player.h"
enum class State{Sleep, Follow, Attack, Flee, PrepareAttack};

class Monster {
public:
	Monster(Player* player);
	void display(sf::RenderWindow& window) const;
	void update();
private:
	void rotateToward(float x1, float y1);
	void moveForward();
	float distanceFromPlayer();
	float x;
	float y;
	float angle;
	float speed = 10;
	float time = 0;
	float const attackRange = 15;
	float const followSpeed = 13;
	float const dashSpeed = 30;
	float const prepareAttackDuration = 0.3f;
	float const attackDuration = 1;
	State action = State::Follow;
	Player* player;
};