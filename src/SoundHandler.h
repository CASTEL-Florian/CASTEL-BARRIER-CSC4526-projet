#pragma once
#include <SFML/Audio.hpp>
#include <iostream>

/**
 * Class managing music and sounds.
 */
class SoundHandler {
public:
	SoundHandler();
	void playMusic();
	void switchToCalm();
	void switchToFrantic();
	void update(sf::Time elapsed);
	void playCoinSound() const;
	void playChestSound() const;
	void playFishSound() const;
	void fadeOut();
	void setUserVolume(float volume);
private:
	std::unique_ptr<sf::Music> calm_music;
	std::unique_ptr<sf::Music> frantic_music;
	std::unique_ptr<sf::Music> coin_sound;
	std::unique_ptr<sf::Music> chest_sound;
	std::unique_ptr<sf::Music> fish_sound;
	sf::Clock timer;
	const float transitionTimeToCalm = 3;
	const float transitionTimeToFrantic = 1;
	float calmTarget = 1;
	float currentVolume = 1;
	float volumeTarget = 1;
	float calmVolume = 1;
	float franticVolume = 1;
	float userVolume = 1;
};