#pragma once
#include <SFML/Audio.hpp>
#include <iostream>

class SoundHandler {
public:
	SoundHandler();
	void playMusic();
	void switchToCalm();
	void switchToFrantic();
	void update(sf::Time elapsed) const;
	void coinSound();
	void chestSound();
private:
	std::unique_ptr<sf::Music> calm_music;
	std::unique_ptr<sf::Music> frantic_music;
	sf::Clock timer;
	const float transitionTimeToCalm = 3;
	const float transitionTimeToFrantic = 1;
	float calmTarget = 100;
};