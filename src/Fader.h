#pragma once
#include <SFML/Graphics.hpp>

enum class FaderState {Sleep, FadeIn, FadeOut};

class Fader {
public:
	Fader(float width, float height);
	void update(sf::Time elapsed);
	void display(sf::RenderWindow& window) const;
	void fadeIn(float fadeDuration = 1);
	void fadeOut(float fadeDuration = 1);
	FaderState getState();
private:
	float width;
	float height;
	float fadeTime = 1;
	float currentTime = 0;
	FaderState state = FaderState::Sleep;
};