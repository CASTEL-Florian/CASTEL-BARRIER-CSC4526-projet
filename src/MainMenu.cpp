#include "MainMenu.h"
#include <cmath>

MainMenu::MainMenu(sf::Texture* backgroundTexture, sf::Texture* playerTexture, Fader* fader, float width, float height) :
	backgroundTexture(backgroundTexture), fader(fader), width(width), height(height)
{
	if (!font.loadFromFile("resources/Pixeled.ttf"))
	{
		std::cout << "Erreur de chargement du fichier Roboto-Regular.ttf";
	}
	gameName.setString("4526 lieues sous les mers");
	gameName.setFont(font);
	gameName.setCharacterSize(50);
	sf::FloatRect gameNameBounds = gameName.getGlobalBounds();
	gameName.setPosition((width - gameNameBounds.width) / 2, 50);

	playText.setString("Jouer");
	playText.setFont(font);
	playText.setCharacterSize(40);
	sf::FloatRect playTextBounds = playText.getGlobalBounds();
	playText.setPosition((width - playTextBounds.width)/2, 250);
	playerAnimator = std::make_unique<Animator>(playerTexture, 3.f, 64, 32, 0.1f, std::vector<int> {14});
	playerAnimator->setPosition(sf::Vector2f(width / 2, height / 2));

	sf::Vector2u backgroundSize = backgroundTexture->getSize();
	backgroundSpriteRect.width = (int)((float)(backgroundHeightProportion * backgroundSize.x) * width / height);
	backgroundSpriteRect.left = (backgroundSize.x - backgroundSpriteRect.width) / 2;
	backgroundSpriteRect.top = 0;
	backgroundSpriteRect.height = (int)(backgroundSize.y * backgroundHeightProportion);
	background.setTexture(*backgroundTexture);
	background.setTextureRect(backgroundSpriteRect);
	float scale = width / (float)backgroundSpriteRect.width;
	background.setScale(sf::Vector2f(scale, scale));

	sea_ambiant = std::make_unique<sf::Music>();
	sea_ambiant->openFromFile("resources/sea_ambiant_sound.wav");
	sea_ambiant->setLoop(true);
	sea_ambiant->setVolume(80);
	sea_ambiant->play();
	diving_music = std::make_unique<sf::Music>();
	diving_music->openFromFile("resources/diving_music.wav");
	diving_music->setLoop(false);
	diving_music->setVolume(50);
}

void MainMenu::update(sf::Time elapsed)
{
	playerAnimator->update(elapsed);
	if (state == MainMenuState::Wait)
		return;
	if (state == MainMenuState::Transition1 || state == MainMenuState::Transition2) {
		transitionTime += elapsed.asSeconds();
		uiAlpha -= elapsed.asSeconds() * 255 / uiFadeTime;
		if (uiAlpha < 0)
			uiAlpha = 0;
		playText.setFillColor(sf::Color(255, 255, 255, uiAlpha));
		playerAnimator->setRotation(70 * easeInOutQuad(transitionTime / playerRoationTime));
		backgroundSpriteRect.top = (int)((backgroundSpriteRect.height - backgroundHeightProportion) * (transitionTime / playerRoationTime) * (transitionTime / playerRoationTime));
		background.setTextureRect(backgroundSpriteRect);
		if (state == MainMenuState::Transition1) {
			if (transitionTime >= startFadeTime) {
				state = MainMenuState::Transition2;
				fader->fadeOut(playerRoationTime - startFadeTime);
			}
		}
		else
		{
			if (fader->getState() == FaderState::Sleep)
				state = MainMenuState::TransitionFinished;
		}
	}
	
	
}

void MainMenu::display(sf::RenderWindow& window) const
{
	window.draw(background);
	playerAnimator->display(window);
	window.draw(gameName);
	window.draw(playText);
}

void MainMenu::mousePressed(int x, int y)
{
	if (playText.getGlobalBounds().contains(sf::Vector2f(x, y))) {
		state = MainMenuState::Transition1;
		diving_music->play();
	}
}

MainMenuState MainMenu::getState() const
{
	return state;
}


float MainMenu::easeInOutQuad(float x) const{
	return x < 0.5 ? 2 * x * x : 1 - std::powf(-2 * x + 2, 2) / 2;
}