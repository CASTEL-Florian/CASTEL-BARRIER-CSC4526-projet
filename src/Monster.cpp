#include "Monster.h"
#include <cmath>

Monster::Monster(Player* player, RoomGenerator* roomGenerator, sf::Texture* texture, float scale, SoundHandler* soundHandler) :
	player(player), roomGenerator(roomGenerator), soundHandler(soundHandler)
{
	std::pair<int, int> farthestRoomPos = roomGenerator->getFarthestRoomPos();
	
	x = (farthestRoomPos.first + 0.5f) * roomWidth* tileWidth;
	y = (farthestRoomPos.second + 0.5f) * roomHeight * tileHeight;
	explore();
	animator = std::make_unique<Animator>(texture, scale, 256, 128, 0.1f, std::vector<int> { 8,10 });
}

/**
 * Display the monster on the window.
 *
 * @param nbMax maximum integer that can be generated.
 * @return the numer generated.
 */
void Monster::display(sf::RenderWindow& window) const {
	animator->setPosition(sf::Vector2f(x, y));
	animator->setRotation(angle + 180);
	if (action == State::Attack|| action == State::PrepareAttack) 
		animator->setMirrored(true, true); 
	else 
		animator->setMirrored(false, true);
	animator->display(window);
}

/**
 * Update the state and the position of the monster.
 *
 * The monster goes to random locations on the map, then sleeps and starts again.
 * When it encounters the player, the monster follows the player and attacks with a
 * dash when the player is close enough. During the dash, the monster can't change direction.
 * After a few seconds, the monster swims away from the player and goes back to it's exploration state.
 * 
 * @param elapsed time since last frame.
 */
void Monster::update(sf::Time elapsed) {
	float distFromPlayer = distanceFromPlayer();
	if (distFromPlayer < hitboxRadius) {
		// The player was too close to the monster and died.
		player->kill(EndType::DeathByMonster);
	}

	if (action == State::Flee) {
		actionTime -= elapsed.asSeconds();
		
		if (actionTime <= 0) {
			sleep(5);
		}
	}
	if (action == State::Explore) {
		rotateToward(targetX, targetY);
		if (std::abs(x - targetX) < tileWidth && std::abs(y - targetY) < tileHeight) {
			sleep(1);
		}
		if (distFromPlayer <= playerDetectRange && player->isAlive()) {
			// The player is close enough for the monster to detect and follow the player.
			follow();
		}
	}
	if (chaseTime <= 0 && action == State::Follow) {
		// The monster stops chasing the player. 
		flee();
	}
	if (action == State::Sleep) {
		actionTime -= elapsed.asSeconds();
		if (distFromPlayer <= playerDetectRange && player->isAlive()) {
			// The player is close enough for the monster to detect and follow the player.
			follow();
		}
		if (actionTime <= 0) {
			explore();
		}
		return;
	}
	if (action == State::Follow && distFromPlayer <= attackRange) {
		// The player is close enough for the monster prepare an attack.
		prepareAttack();
	}
	if (action == State::PrepareAttack) {
		actionTime -= elapsed.asSeconds();
		chaseTime -= elapsed.asSeconds();
		
		if (actionTime < 0) {
			dash();
		}

	}
	if (action == State::Attack) {
		actionTime -= elapsed.asSeconds();
		chaseTime -= elapsed.asSeconds();
		if (actionTime < 0) {
			follow();
		}
	}
	if (action == State::Follow) {
		chaseTime -= elapsed.asSeconds();
		rotateToward(player->get_x(), player->get_y());
	}
	moveForward(elapsed);
	if (action == State::Attack) 
		animator->playAnimation(1);
	else
		animator->playAnimation(0);
	animator->update(elapsed);
}

/**
 * Get the monster x position.
 *
 * @return x position of the monster.
 */
float Monster::get_x() const
{
	return x;
}

/**
 * Get the monster y position.
 *
 * @return y position of the monster.
 */
float Monster::get_y() const
{
	return y;
}

/**
 * Rotate the monster toward a certain point.
 *
 * @param x1 x position of the point.
 * @param y1 y position of the point.
 */
void Monster::rotateToward(float x1, float y1)
{
	sf::Vector2f dir(x1 - x, y1 - y);
	if (dir.x == 0) {
		if (dir.y >= 0)
			angle = 90;
		else
			angle = -90;
		return;
	}
	if (dir.x > 0) {
		angle = std::atan(dir.y / dir.x) * (180 / b2_pi);
	}
	else
	{
		angle = 180 + std::atan(dir.y / dir.x) * (180 / b2_pi);
	}
}

/**
 * Move the monster forward.
 */
void Monster::moveForward(sf::Time elapsed)
{
	x += std::cos(angle * b2_pi / 180) * speed * elapsed.asSeconds();
	y += std::sin(angle * b2_pi / 180) * speed * elapsed.asSeconds();
}

/**
 * Get the distance between the monster and the player.
 *
 * @return the distance from the player.
 */
float Monster::distanceFromPlayer() const
{
	sf::Vector2f dir(player->get_x() - x, player->get_y() - y);
	return std::sqrt(dir.x*dir.x + dir.y * dir.y);
}

/**
 * Get a random position on the map.
 *
 * @return the random position on the map.
 */
std::pair<float, float> Monster::getRandomMapPosition()
{
	auto roomPos = roomGenerator->getRandomRoomPos();
	std::pair<float, float> pos(roomPos.first * roomWidth* tileWidth, roomPos.second * roomHeight * tileHeight);
	pos.first += (random_1_to_n(roomWidth) - 1) * tileWidth;
	pos.second += (random_1_to_n(roomHeight) - 1) * tileHeight;
	return pos;
}

/**
 * Start exploring.
 */
void Monster::explore()
{
	action = State::Explore;
	auto pos = getRandomMapPosition();
	targetX = pos.first;
	targetY = pos.second;
	speed = followSpeed;
}

/**
 * Start sleeping (not moving).
 * 
 * @param duration of the sleeping state.
 */
void Monster::sleep(float duration)
{
	action = State::Sleep;
	chaseTime = chaseDuration;
	actionTime = duration;
}

/**
 * Start dashing forward.
 */
void Monster::dash()
{
	action = State::Attack;
	speed = dashSpeed;
	actionTime = attackDuration;
}

/**
 * Start following the player.
 */
void Monster::follow()
{
	if (!player->isAlive()) {
		explore();
		return;
	}
	soundHandler->switchToFrantic();
	action = State::Follow;
	speed = followSpeed;
}

/**
 * Stop moving and start preparing an attack.
 */
void Monster::prepareAttack()
{
	action = State::PrepareAttack;
	actionTime = prepareAttackDuration;
	speed = 0;
}

/**
 * Start moving away from the player.
 */
void Monster::flee()
{
	action = State::Flee;
	actionTime = 5;
	speed = followSpeed/2;
	rotateToward(2 * x - player->get_x(), 2 * y - player->get_y()); // Rotate away from the player.
	soundHandler->switchToCalm();
}
