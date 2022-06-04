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
