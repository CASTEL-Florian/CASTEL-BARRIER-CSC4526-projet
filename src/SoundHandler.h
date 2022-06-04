#pragma once
#include <SFML/Audio.hpp>

class SoundHandler {
public:
	SoundHandler();
	void playMusic();
	void switchToCalm();
	void switchToFrantic();
	void coinSound();
	void chestSound();
private:
	std::unique_ptr<sf::Music> calm_music;
	std::unique_ptr<sf::Music> frantic_music;
	sf::Clock timer;
};