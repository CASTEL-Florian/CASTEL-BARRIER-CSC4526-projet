#include "EndScreen.h"

EndScreen::EndScreen(sf::Texture* backgroundTexture, sf::Texture* coinTexture, sf::Texture* treasureTexture, Fader* fader, float width, float height) :
	backgroundTexture(backgroundTexture), fader(fader), width(width), height(height)
{
	coinAnimator = std::make_unique<Animator>(coinTexture, 3.f, 16, 16, 0.1f, std::vector<int> {14});

	treasureAnimator = std::make_unique<Animator>(treasureTexture, 3.f, 32, 32, 0.1f, std::vector<int> {12});
}

void EndScreen::update(sf::Time elapsed)
{
	coinAnimator->update(elapsed);
	treasureAnimator->update(elapsed);
}

void EndScreen::display(sf::RenderWindow& window) const
{
	coinAnimator->display(window);
	treasureAnimator->display(window);
}

void EndScreen::mousePressed(int x, int y)
{
}
