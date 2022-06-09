#include "Fish.h"
#include "FishSpawner.h"
#include "RoomGenerator.h"

Fish::Fish(sf::Texture* texture, Player* player,float scale, float x, float y, SoundHandler* soundHandler) : 
	player(player), x(x), y(y), soundHandler(soundHandler)
{
	animator = std::make_unique<Animator>(texture, scale, 32, 16, 0.1f, std::vector<int> {18, 18});
	animator->playAnimation(random_1_to_n(2) - 1);
}

/**
 * Update the fish.
 * 
 * Every actionTime seconds, the fish chooses randomly a new FishAction. Either the fish moves left
 * or right or it stops. If the player is too close, the fish flees in the opposite direction.
 *
 * @param elapsed time since last frame.
 */
void Fish::update(sf::Time elapsed)
{
	actionTime -= elapsed.asSeconds();
	if (action != FishAction::Flee && distanceFromPlayer() < fleeDistance) {
		action = FishAction::Flee;
		soundHandler->playFishSound();
		rotateToward(2 * x - player->get_x(), 2 * y - player->get_y());
		speed = fleeSpeed;
	}
	if (action == FishAction::Flee) {
		x += std::cos(angle * b2_pi / 180) * speed * elapsed.asSeconds();
		y += std::sin(angle * b2_pi / 180) * speed * elapsed.asSeconds();
		return;
	}
	if (actionTime <= 0) {
		actionTime = actionDuration;
		action = (FishAction)(random_1_to_n(3) - 1);
	}
	if (action == FishAction::Stop) {
		if (speed > 0) {
			speed -= acceleration;
			if (speed < 0)
				speed = 0;
		}
		if (speed < 0) {
			speed += acceleration;
			if (speed > 0)
				speed = 0;
		}
	}
	else if (action == FishAction::MoveLeft) {
		speed -= acceleration;
		if (speed < -maxSpeed)
			speed = -maxSpeed;
	}
	else {
		speed += acceleration;
		if (speed > maxSpeed)
			speed = maxSpeed;
	}
	x += speed * elapsed.asSeconds();
	animator->update(elapsed);
}

/**
 * Display the fish on the window.
 *
 * @param window on which the fish is drawn.
 */
void Fish::display(sf::RenderWindow& window) const
{
	if (angle > 90 && angle < 270)
		animator->setMirrored(true, true, true);
	else if (speed < 0)
		animator->setMirrored(false, true);
	else
		animator->setMirrored(true, true);
	animator->setPosition(sf::Vector2f(x, y));
	animator->setRotation(angle);
	animator->display(window);
}

/**
 * Get the x position of the fish.
 *
 * @return x position of the fish.
 */
float Fish::get_x() const
{
	return x;
}

/**
 * Get the y position of the fish.
 *
 * @return y position of the fish.
 */
float Fish::get_y() const
{
	return y;
}

/**
 * Initialize the position of the fish.
 *
 * @param posX x position of the fish.
 * @param posY y position of the fish.
 */
void Fish::init(float posX, float posY)
{
	x = posX;
	y = posY;
	angle = 0;
	speed = 0;
	action = FishAction::Stop;
	animator->playAnimation(random_1_to_n(2) - 1);
}

/**
 * Get the distance between the fish and the player.
 *
 * @return distance from the player.
 */
float Fish::distanceFromPlayer() const
{
	sf::Vector2f dir(player->get_x() - x, player->get_y() - y);
	return std::sqrt(dir.x * dir.x + dir.y * dir.y);
}

/**
 * Rotate the fish toward a certain point.
 *
 * @param x1 x position of the point.
 * @param y1 y position of the point.
 */

void Fish::rotateToward(float x1, float y1)
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