#include "EndScreen.h"

EndScreen::EndScreen(sf::Texture* backgroundTexture, sf::Texture* coinTexture, sf::Texture* treasureTexture, Fader* fader, const TreasureManager* treasureManager, SoundHandler* soundHandler, float width, float height) :
	fader(fader), soundHandler(soundHandler), backgroundTexture(backgroundTexture), width(width), height(height)
{
	if (!font.loadFromFile("resources/Pixeled.ttf"))
	{
		std::cout << "Erreur de chargement du fichier Roboto-Regular.ttf";
	}
	int treasuresFoundCount = treasureManager ? treasureManager->getTreasuresFoundCount() : 42;
	int coinFoundCount = treasureManager ? treasureManager->getCoinFoundCount() : 42;
	returnText.setFont(font);
	returnText.setString("Retourner au menu principal");
	returnText.setCharacterSize(40);
	returnText.setOutlineThickness(3.f);
	treasureText.setFont(font);
	treasureText.setString("Trésors : " + std::to_string(treasuresFoundCount) + "/" + std::to_string(treasuresCount));
	treasureText.setCharacterSize(30);
	treasureText.setPosition(300, 320);
	treasureText.setOutlineThickness(3.f);
	coinText.setFont(font);
	coinText.setString("Pièces : " + std::to_string(coinFoundCount) + "/" + std::to_string(coinCount));
	coinText.setCharacterSize(30);
	coinText.setPosition(300, 420);
	coinText.setOutlineThickness(3.f);
	sf::FloatRect returnTextBounds = returnText.getGlobalBounds();
	returnText.setPosition((width - returnTextBounds.width) / 2, 700);

	treasureAnimator = std::make_unique<Animator>(treasureTexture, 3.f, 32, 32, 0.1f, std::vector<int> {12});
	treasureAnimator->setPosition(sf::Vector2f(225, 325));
	coinAnimator = std::make_unique<Animator>(coinTexture, 3.f, 16, 16, 0.1f, std::vector<int> {14});
	coinAnimator->setPosition(sf::Vector2f(225, 425));

	sf::Vector2u backgroundSize = backgroundTexture->getSize();
	background.setTexture(*backgroundTexture);
	float backgroundScale = std::max(width / (float)backgroundSize.x, height / (float)backgroundSize.y);
	background.setScale(sf::Vector2f(backgroundScale, backgroundScale));

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
	window.draw(background);
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
