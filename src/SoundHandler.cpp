#include "SoundHandler.h"

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
	if (calm_music->getVolume() < 90) {
		if (timer.getElapsedTime().asMilliseconds() >= 100) {
			calm_music->setVolume(calm_music->getVolume() + 10);
			frantic_music->setVolume(frantic_music->getVolume() - 10);
			timer.restart();
		}
	}
}

void SoundHandler::switchToFrantic() {
	if (frantic_music->getVolume() < 90) {
		if (timer.getElapsedTime().asMilliseconds() >= 100) {
			frantic_music->setVolume(frantic_music->getVolume() + 10);
			calm_music->setVolume(calm_music->getVolume() - 10);
			timer.restart();
		}
	}
}