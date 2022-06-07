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
}

void SoundHandler::playMusic() {
	calm_music->play();
	frantic_music->play();
}

void SoundHandler::switchToCalm() {
	calmTarget = 1;
}

void SoundHandler::switchToFrantic() {
	calmTarget = 0;
}

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

void SoundHandler::fadeOut()
{
	volumeTarget = 0;
}

void SoundHandler::setUserVolume(float volume)
{
	userVolume = volume;
}

void SoundHandler::playCoinSound() const {
	coin_sound->stop();
	coin_sound->setVolume(25 * currentVolume * userVolume);
	coin_sound->play();
}

void SoundHandler::playChestSound() const {
	chest_sound->stop();
	chest_sound->setVolume(35 * currentVolume * userVolume);
	chest_sound->play();
}

void SoundHandler::playFishSound() const {
	fish_sound->stop();
	fish_sound->setVolume(15 * currentVolume * userVolume);
	fish_sound->play();
}
