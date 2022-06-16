#include "Player.h"
#include "Player.h"
#include <cmath>


Player::Player(b2World* world, const float enginePower, sf::Texture* texture, float scale) :
	enginePower(enginePower)
{
	animator = std::make_unique<Animator>(texture, scale, 64, 32, 0.1f, std::vector<int> {14});
	sf::FloatRect bounds = animator->getLocalBounds();
	w = bounds.width * scale;
	h = bounds.height * scale;
	initBox(world, b2Vec2(roomWidth * tileWidth / 2, roomHeight * tileHeight / 2), b2_dynamicBody);
}

/**
 * Move the player.
 *
 * @param vec vector of the force to apply
 */
void Player::move(const b2Vec2& vec) {
	// Can't control the player when not alive.
	if (!alive)
		return;
	// Apply a force not exactly at the center of the player to make it rotate.
	body->ApplyForce(b2Vec2(vec.x * enginePower, vec.y * enginePower), 
		body->GetPosition() + b2Vec2(w * std::cos(body->GetAngle()) / 5, w * std::sin(body->GetAngle()) / 5),
		true);
}

void Player::boost()
{
	body->ApplyForce(b2Vec2(std::cos(body->GetAngle()) * enginePower, std::sin(body->GetAngle()) * enginePower), body->GetPosition(), true);
}

/**
 * Update values of player.
 *
 * @param elapsed time elapsed since last frame
 */
void Player::update(sf::Time elapsed) {
	x = body->GetPosition().x;
	y = -body->GetPosition().y;
	rota = -body->GetAngle();
	animator->update(elapsed);
}

/**
 * Display the player.
 *
 * @param window window in which to render
 */
void Player::display(sf::RenderWindow& window) const{
	animator->setPosition(sf::Vector2f(x, y));
	animator->setRotation(rota * 180.0f / b2_pi);

	// Mirror the sprite of the player when facing to the left.
	float rotaDegree = rota * 180 / b2_pi;
	if (float rota360 = rotaDegree - std::floor(rotaDegree / 360) * 360; rota360 > 90 && rota360 < 270)
		animator->setMirrored(true);
	else
		animator->setMirrored(false);
	animator->display(window);
}

/**
 * Display a darkness filter around the "torch" of the player.
 *
 * @param window window in which to render
 */
void Player::renderLight(sf::RenderWindow& window) const {
	sf::ConvexShape polygon1;
	polygon1.setPointCount(7);
	polygon1.setPoint(0, sf::Vector2f(0, 0));
	polygon1.setPoint(1, sf::Vector2f(0, 170));
	polygon1.setPoint(2, sf::Vector2f(65, 170));
	polygon1.setPoint(3, sf::Vector2f(85, 90));
	polygon1.setPoint(4, sf::Vector2f(105, 170));
	polygon1.setPoint(5, sf::Vector2f(170, 170));
	polygon1.setPoint(6, sf::Vector2f(170, 0));
	polygon1.setFillColor(sf::Color(0, 0, 15, 230));
	polygon1.setOrigin(sf::Vector2f(85, 90));
	polygon1.setRotation(rota * 180.0f / b2_pi - 90.f);
	polygon1.setPosition(x + w / 2 * std::cos(rota), y + w / 2 * std::sin(rota));
	window.draw(polygon1);

	sf::ConvexShape polygon2;
	polygon2.setPointCount(7);
	polygon2.setPoint(0, sf::Vector2f(92.5f, 120));
	polygon2.setPoint(1, sf::Vector2f(90, 122.5f));
	polygon2.setPoint(2, sf::Vector2f(85, 124.f));
	polygon2.setPoint(3, sf::Vector2f(80, 122.5f));
	polygon2.setPoint(4, sf::Vector2f(77.5f, 120));
	polygon2.setPoint(5, sf::Vector2f(65, 170));
	polygon2.setPoint(6, sf::Vector2f(105, 170));
	polygon2.setFillColor(sf::Color(0, 0, 15, 230));
	polygon2.setOrigin(sf::Vector2f(85, 90));
	polygon2.setRotation(rota * 180.0f / b2_pi - 90.f);
	polygon2.setPosition(x + w / 2 * std::cos(rota), y + w / 2 * std::sin(rota));
	window.draw(polygon2);
}

/**
 * Updates the room in which the player roams.
 *
 */
void Player::updateRoomPosition()
{
	roomX = std::floor(x / (roomWidth * tileWidth));
	roomY = std::floor(y / (roomHeight * tileHeight));
}

/**
 * Player.roomX getter.
 *
 */
int Player::getRoomX() const
{
	return roomX;
}

/**
 * Player.roomY getter.
 *
 */
int Player::getRoomY() const
{
	return roomY;
}

/**
 * Player.x getter.
 *
 */
float Player::get_x() const
{
	return x;
}

/**
 * Player.y getter.
 *
 */
float Player::get_y() const
{
	return y;
}

/**
 * Tell if player is alive or not.
 *
 */
bool Player::isAlive() const
{
	return alive;
}

/**
 * Kill the player. The player can no longer be controled by the player.
 *
 * @param end type of ending (DeathByMonster or Drawning)
 */
void Player::kill(EndType end)
{
	alive = false;
	endType = end;
}

/**
 * Player.endType getter.
 *
 */
EndType Player::getEndType() const
{
	return endType;
}


