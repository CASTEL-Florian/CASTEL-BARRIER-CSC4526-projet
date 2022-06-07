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
	calmTarget = 1;
}

void SoundHandler::switchToFrantic() {
	calmTarget = 0;
}

void SoundHandler::update(sf::Time elapsed)
{
	if (volumeTarget < currentVolume) {
		currentVolume = std::max(0.f, currentVolume - elapsed.asSeconds() * volume);
	}
	
	if (calmVolume < calmTarget) {
		calmVolume = std::min(calmVolume + (elapsed.asSeconds() / transitionTimeToCalm), calmTarget);
	}
	if (calmVolume > calmTarget) {
		calmVolume = std::max(calmVolume - (elapsed.asSeconds() / transitionTimeToFrantic), calmTarget);
	}
	franticVolume = 1 - calmVolume;
	calm_music->setVolume(calmVolume * 100 * currentVolume);
	frantic_music->setVolume(franticVolume * 100 * currentVolume);
}

void SoundHandler::fadeOut()
{
	volumeTarget = 0;
}
