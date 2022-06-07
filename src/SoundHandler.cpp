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
	calmTarget = 100;
}

void SoundHandler::switchToFrantic() {
	calmTarget = 0;
}

void SoundHandler::update(sf::Time elapsed) const
{
	if (calm_music->getVolume() < calmTarget) {
		calm_music->setVolume(std::min(calm_music->getVolume() + (100 * elapsed.asSeconds() / transitionTimeToCalm), calmTarget));
		frantic_music->setVolume(100 - calm_music->getVolume());
	}
	if (calm_music->getVolume() > calmTarget) {
		calm_music->setVolume(std::max(calm_music->getVolume() - (100 * elapsed.asSeconds() / transitionTimeToFrantic), calmTarget));
		frantic_music->setVolume(100 - calm_music->getVolume());
	}
}

void SoundHandler::playCoinSound() {
	coin_sound->stop();
	coin_sound->play();
}

void SoundHandler::playChestSound() {
	chest_sound->stop();
	chest_sound->play();
}

void SoundHandler::playFishSound() {
	fish_sound->stop();
	fish_sound->play();
}
