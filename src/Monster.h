#pragma once
#include "Player.h"
#include "RoomGenerator.h"
#include "SoundHandler.h"

/**
 * State of the monster. The behaviour of the monster is different depending on the state it is in.
 */
enum class State{
	/// The monster doesn't move. The monster waits for the player to get closer or the end of the state.
	Sleep,
	/// The monster follows the player.
	Follow,
	/// The monster dashes forward.
	Attack,
	/// The monster follows the player.
	Flee,
	/// The monster moves forward (after turning away from the player).
	PrepareAttack,
	/// The monster moves toward a random point on the map.
	Explore
};

/**
 * The monster explores the map. When it encounters the player, the monster attacks it for
 * a moment before exploring again.
 */
class Monster : public Object{
public:
	Monster(Player* player, RoomGenerator* roomGenerator, sf::Texture* texture, float scale, SoundHandler* soundHandler);
	void display(sf::RenderWindow& window) const override;
	void update(sf::Time elapsed) override;
	float get_x() const override;
	float get_y() const override;
private:
	void rotateToward(float x1, float y1);
	void moveForward(sf::Time elapsed);
	float distanceFromPlayer() const;
	std::pair<float,float> getRandomMapPosition() const;
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
	const float chaseDuration = 13;
	float chaseTime = 13;
	float targetX = 0;
	float targetY = 0;
	float const attackRange = 20;
	float const followSpeed = 13;
	float const dashSpeed = 30;
	float const prepareAttackDuration = 0.3f;// 1.f;
	float const attackDuration = 1;
	float const playerDetectRange = 60;
	float const hitboxRadius = 8;
	State action = State::Sleep;
	Player* player;
	RoomGenerator* roomGenerator;

	SoundHandler* soundHandler;
};