#include "Fader.h"

Fader::Fader(float width, float height) : width(width), height(height)
{
}

/**
 * Update the values of the fader.
 *
 * @param elapsed time elapsed since last frame
 */
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

/**
 * Display the fader.
 *
 * @param window window in which to render
 */
void Fader::display(sf::RenderWindow& window) const
{
	sf::RectangleShape rect;
	rect.setFillColor(sf::Color(fadeColor.r, fadeColor.g, fadeColor.b, 255 * currentTime / fadeTime));
	rect.setSize(sf::Vector2f(width, height));
	window.draw(rect);
}

/**
 * Fade in.
 *
 * @param fadeDuration duration of the fade
 */
void Fader::fadeIn(float fadeDuration)
{
	fadeTime = fadeDuration;
	currentTime = fadeTime;
	state = FaderState::FadeIn;
}

/**
 * Fade out.
 *
 * @param fadeDuration duration of the fade
 */
void Fader::fadeOut(float fadeDuration)
{
	fadeTime = fadeDuration;
	currentTime = 0;
	state = FaderState::FadeOut;
}

/**
 * Fader.state getter.
 *
 */
FaderState Fader::getState() const
{
	return state;
}

/**
 * Set the color of the fade.
 *
 * @param color color of the fade
 */
void Fader::setFadeColor(sf::Color color)
{
	fadeColor = color;
}
