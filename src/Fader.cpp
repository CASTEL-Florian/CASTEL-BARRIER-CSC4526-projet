#include "Fader.h"

Fader::Fader(float width, float height) : width(width), height(height)
{
}

void Fader::update(sf::Time elapsed)
{
	if (state == FaderState::FadeOut) {
		currentTime += elapsed.asSeconds();
		if (currentTime > fadeTime) {
			currentTime = fadeTime;
			state = FaderState::Sleep;
		}
	}
	if (state == FaderState::FadeIn) {
		if (flag) {
			flag = false;
			currentTime -= 1 / 60.f;
		}
		else
			currentTime -= elapsed.asSeconds();
		if (currentTime < 0) {
			currentTime = 0;
			state = FaderState::Sleep;
		}
	}
}

void Fader::display(sf::RenderWindow& window) const
{
	sf::RectangleShape rect;
	rect.setFillColor(sf::Color(0, 0, 0, 255 * currentTime / fadeTime));
	rect.setSize(sf::Vector2f(width, height));
	window.draw(rect);
}

void Fader::fadeIn(float fadeDuration, bool ignoreFirstFrame)
{
	flag = ignoreFirstFrame;
	fadeTime = fadeDuration;
	currentTime = fadeTime;
	state = FaderState::FadeIn;
}

void Fader::fadeOut(float fadeDuration)
{
	fadeTime = fadeDuration;
	currentTime = 0;
	state = FaderState::FadeOut;
}

FaderState Fader::getState()
{
	return state;
}
