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
	rect.setFillColor(sf::Color(fadeColor.r, fadeColor.g, fadeColor.b, 255 * currentTime / fadeTime));
	rect.setSize(sf::Vector2f(width, height));
	window.draw(rect);
}

void Fader::fadeIn(float fadeDuration)
{
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

FaderState Fader::getState() const
{
	return state;
}

void Fader::setFadeColor(sf::Color color)
{
	fadeColor = color;
}
