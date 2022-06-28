#include "SoundHandler.h"
#include <algorithm>

SoundHandler::SoundHandler() 
{
	calm_music = std::make_unique<sf::Music>();
	calm_music->openFromFile("resources/calm_music.wav");
	calm_music->setLoop(true);
	calm_music->setVolume(100);

	frantic_music = std::make_unique<sf::Music>();
	frantic_music->openFromFile("resources/frantic_music.wav");
	frantic_music->setLoop(true);
	frantic_music->setVolume(0);

	coin_sound = std::make_unique<sf::Music>();
	coin_sound->openFromFile("resources/coin_sound.wav");
	coin_sound->setVolume(25);
	chest_sound = std::make_unique<sf::Music>();
	chest_sound->openFromFile("resources/chest_sound.wav");
	chest_sound->setVolume(35);
	fish_sound = std::make_unique<sf::Music>();
	fish_sound->openFromFile("resources/fish_sound.wav");
	fish_sound->setVolume(15);
	bubble_sound = std::make_unique<sf::Music>();
	bubble_sound->openFromFile("resources/bubble.wav");
	bubble_sound->setVolume(50);
	boost_sound = std::make_unique<sf::Music>();
	boost_sound->openFromFile("resources/boost_bubble.wav");
	boost_sound->setVolume(50);
}

/**
 * Play music.
 *
 */
void SoundHandler::playMusic() const{
	calm_music->play();
	frantic_music->play();
}

/**
 * Set the target volume of played music to switch to calm.
 *
 */
void SoundHandler::switchToCalm() {
	calmTarget = 1;
}

/**
 * Set the target volume of played music to switch to frantic.
 *
 */
void SoundHandler::switchToFrantic() {
	calmTarget = 0;
}

/**
 * Update volumes of played music.
 *
 * @param elapsed time elapsed since last frame
 */
void SoundHandler::update(sf::Time elapsed)
{
	if (volumeTarget < currentVolume) {
		currentVolume = std::max(0.f, currentVolume - elapsed.asSeconds() * userVolume);
	}
	
	if (calmVolume < calmTarget) {
		calmVolume = std::min(calmVolume + (elapsed.asSeconds() / transitionTimeToCalm), calmTarget);
	}
	if (calmVolume > calmTarget) {
		calmVolume = std::max(calmVolume - (elapsed.asSeconds() / transitionTimeToFrantic), calmTarget);
	}
	franticVolume = 1 - calmVolume;
	calm_music->setVolume(calmVolume * 100 * currentVolume * userVolume);
	frantic_music->setVolume(franticVolume * 100 * currentVolume * userVolume);
}

/**
 * Set volume target to fade out played music.
 *
 */
void SoundHandler::fadeOut()
{
	volumeTarget = 0;
}

/**
 * Set volume as intended by user.
 *
 * @param volume desired volume
 */
void SoundHandler::setUserVolume(float volume)
{
	userVolume = volume;
}

/**
 * Play sound of coin.
 *
 */
void SoundHandler::playCoinSound() const {
	coin_sound->stop();
	coin_sound->setVolume(25 * currentVolume * userVolume);
	coin_sound->play();
}

/**
 * Play sound of chest.
 *
 */
void SoundHandler::playChestSound() const {
	chest_sound->stop();
	chest_sound->setVolume(35 * currentVolume * userVolume);
	chest_sound->play();
}

/**
 * Play sound of fish.
 *
 */
void SoundHandler::playFishSound() const {
	fish_sound->stop();
	fish_sound->setVolume(15 * currentVolume * userVolume);
	fish_sound->play();
}

/**
* Play sound of bubble.
* 
*/
void SoundHandler::playBubbleSound() const {
	bubble_sound->stop();
	bubble_sound->setVolume(50 * currentVolume * userVolume);
	bubble_sound->play();
}

/**
* Play sound of boost.
* 
*/
void SoundHandler::playBoostSound() const {
	boost_sound->stop();
	boost_sound->setVolume(50 * currentVolume * userVolume);
	boost_sound->play();
}
