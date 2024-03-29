#include "EndScreen.h"
#include <sstream>
#include <iomanip>

EndScreen::EndScreen(std::vector<sf::Texture>* textures, Fader* fader, const TreasureManager* treasureManager, SoundHandler* soundHandler, float time, float width, float height, int backgroundId) :
	fader(fader), soundHandler(soundHandler), backgroundTexture(backgroundTexture), width(width), height(height)
{
	sf::Texture* backgroundTexture = &(*textures)[backgroundId];
	sf::Texture* coinTexture = &(*textures)[4];
	sf::Texture* treasureTexture = &(*textures)[5];
	if (!font.loadFromFile("resources/Pixeled.ttf"))
	{
		std::cout << "Erreur de chargement du fichier Roboto-Regular.ttf";
	}
	int treasuresFoundCount = treasureManager ? treasureManager->getTreasuresFoundCount() : 0;
	int coinFoundCount = treasureManager ? treasureManager->getCoinFoundCount() : 0;
	returnText.setFont(font);
	returnText.setString("Retourner au menu principal");
	returnText.setCharacterSize(40);
	returnText.setOutlineThickness(3.f);
	treasureText.setFont(font);
	treasureText.setString("Tr�sors : " + std::to_string(treasuresFoundCount) + "/" + std::to_string(treasuresCount));
	treasureText.setCharacterSize(30);
	treasureText.setPosition(300, 220);
	treasureText.setOutlineThickness(3.f);
	coinText.setFont(font);
	coinText.setString("Pi�ces : " + std::to_string(coinFoundCount) + "/" + std::to_string(coinCount));
	coinText.setCharacterSize(30);
	coinText.setPosition(300, 320);
	coinText.setOutlineThickness(3.f);
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << time;
	timeText.setFont(font);
	timeText.setString("Temps : " + stream.str() + "s");
	timeText.setCharacterSize(30);
	timeText.setPosition(300, 420);
	timeText.setOutlineThickness(3.f);

	int score = (coinFoundCount * coinScore) + (treasuresFoundCount * treasureScore);

	if (backgroundId == 10) {
		score += (int)(std::exp2f(-time * timeScoreDecreaseSpeed) * (float)timeScore);
		if (coinFoundCount == coinCount) {
			score += allCoinsBonus;
		}
	}
	scoreText.setFont(font);
	scoreText.setString("Score : " + std::to_string(score));
	scoreText.setCharacterSize(30);
	scoreText.setPosition(300, 520);
	scoreText.setOutlineThickness(3.f);
	sf::FloatRect returnTextBounds = returnText.getGlobalBounds();
	returnText.setPosition((width - returnTextBounds.width) / 2, 700);

	treasureAnimator = std::make_unique<Animator>(treasureTexture, 3.f, 32, 32, 0.1f, std::vector<int> {12});
	treasureAnimator->setPosition(sf::Vector2f(225, 225));
	coinAnimator = std::make_unique<Animator>(coinTexture, 3.f, 16, 16, 0.1f, std::vector<int> {14});
	coinAnimator->setPosition(sf::Vector2f(225, 325));

	sf::Vector2u backgroundSize = backgroundTexture->getSize();
	background.setTexture(*backgroundTexture);
	float backgroundScale = std::max(width / (float)backgroundSize.x, height / (float)backgroundSize.y);
	background.setScale(sf::Vector2f(backgroundScale, backgroundScale));

}

/**
 * EndScreen.state getter
 *
 */
EndScreenState EndScreen::getState() const
{
	return state;
}

/**
 * Update the values of the end screen, calls the updates of rendered sprites.
 *
 * @param elapsed time elapsed since last frame
 */
void EndScreen::update(sf::Time elapsed)
{
	if (state == EndScreenState::Transition && fader->getState() == FaderState::Sleep) {
		state = EndScreenState::TransitionFinished;
	}
	coinAnimator->update(elapsed);
	treasureAnimator->update(elapsed);
}

/**
 * Display the end screen.
 *
 * @param window window in which to render
 */
void EndScreen::display(sf::RenderWindow& window) const
{
	window.draw(background);
	coinAnimator->display(window);
	treasureAnimator->display(window);
	window.draw(coinText);
	window.draw(treasureText);
	window.draw(timeText);
	window.draw(scoreText);
	window.draw(returnText);
}

/**
 * Check if mouse is pressed on return text and if so transition to main menu.
 *
 * @param x x coordinate of the mouse when pressed
 * @param y y coordinate of the mouse when pressed
 */
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
