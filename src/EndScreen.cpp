#include "EndScreen.h"

EndScreen::EndScreen(sf::Texture* backgroundTexture, sf::Texture* coinTexture, sf::Texture* treasureTexture, Fader* fader, const TreasureManager* treasureManager, SoundHandler* soundHandler, float width, float height) :
	fader(fader), backgroundTexture(backgroundTexture), soundHandler(soundHandler), width(width), height(height)
{
	if (!font.loadFromFile("resources/Roboto-Regular.ttf"))
	{
		std::cout << "Erreur de chargement du fichier Roboto-Regular.ttf";
	}
	int treasuresFoundCount = treasureManager ? treasureManager->getTreasuresFoundCount() : 42;
	int coinFoundCount = treasureManager ? treasureManager->getCoinFoundCount() : 42;
	returnText.setFont(font);
	returnText.setString("Retourner au menu principal");
	returnText.setCharacterSize(50);
	treasureText.setFont(font);
	treasureText.setString("Trésors : " + std::to_string(treasuresFoundCount) + "/" + std::to_string(treasuresCount));
	treasureText.setCharacterSize(50);
	treasureText.setPosition(300, 300);
	coinText.setFont(font);
	coinText.setString("Pièces : " + std::to_string(coinFoundCount) + "/" + std::to_string(coinCount));
	coinText.setCharacterSize(50);
	coinText.setPosition(300, 400);
	sf::FloatRect returnTextBounds = returnText.getGlobalBounds();
	returnText.setPosition((width - returnTextBounds.width) / 2, 700);

	treasureAnimator = std::make_unique<Animator>(treasureTexture, 3.f, 32, 32, 0.1f, std::vector<int> {12});
	treasureAnimator->setPosition(sf::Vector2f(225, 325));
	coinAnimator = std::make_unique<Animator>(coinTexture, 3.f, 16, 16, 0.1f, std::vector<int> {14});
	coinAnimator->setPosition(sf::Vector2f(225, 425));

}

EndScreenState EndScreen::getState() const
{
	return state;
}

void EndScreen::update(sf::Time elapsed)
{
	if (state == EndScreenState::Transition && fader->getState() == FaderState::Sleep) {
		state = EndScreenState::TransitionFinished;
	}
	coinAnimator->update(elapsed);
	treasureAnimator->update(elapsed);
}

void EndScreen::display(sf::RenderWindow& window) const
{
	coinAnimator->display(window);
	treasureAnimator->display(window);
	window.draw(coinText);
	window.draw(treasureText);
	window.draw(returnText);
}

void EndScreen::mousePressed(int x, int y)
{
	if (state == EndScreenState::Wait && returnText.getGlobalBounds().contains(sf::Vector2f(x, y))) {
		fader->setFadeColor(sf::Color::Black);
		fader->fadeOut();
		if (soundHandler)
			soundHandler->fadeOut();
		state = EndScreenState::Transition;
	}
}
