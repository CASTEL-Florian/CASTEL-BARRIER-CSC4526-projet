#include "MainMenu.h"
#include <cmath>

MainMenu::MainMenu(sf::Texture* backgroundTexture, sf::Texture* playerTexture, Fader* fader, float width, float height) :
	backgroundTexture(backgroundTexture), fader(fader), width(width), height(height)
{
	if (!font.loadFromFile("resources/Pixeled.ttf"))
	{
		std::cout << "Erreur de chargement du fichier Pixeled.ttf";
	}
	gameName.setString("4526 lieues sous les mers");
	gameName.setFont(font);
	gameName.setCharacterSize(50);
	sf::FloatRect gameNameBounds = gameName.getGlobalBounds();
	gameName.setPosition((width - gameNameBounds.width) / 2, 50);

	playText.setString("Jouer");
	playText.setFont(font);
	playText.setCharacterSize(40);
	playText.setOutlineThickness(3.f);
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

	volumeBar.setPosition(volumeBarX, volumeBarY);
	volumeBarWhite.setPosition(volumeBar.getPosition());
	volumeBar.setSize(sf::Vector2f(volumeBarWidth, volumeBarHeight));
	volumeMouseBox.left = volumeBarX - 10;
	volumeMouseBox.top = volumeBarY - 10;
	volumeMouseBox.width = volumeBarWidth + 20;
	volumeMouseBox.height = volumeBarHeight + 20;

	volumeText.setFont(font);
	volumeText.setString("Volume");
	volumeText.setCharacterSize(20);
	volumeText.setPosition(volumeBarX - 150, volumeBarY - 5);
}

/**
 * Easing function for player rotation during the transition.
 */
float easeInOutQuad(float x) {
	return x < 0.5 ? 2 * x * x : 1 - std::powf(-2 * x + 2, 2) / 2;
}

/**
 * Update the main menu.
 *
 * @param elapsed time since last frame.
 */
void MainMenu::update(sf::Time elapsed)
{

	playerAnimator->update(elapsed);


	volumeBar.setFillColor(sf::Color(100, 100, 100, uiAlpha));
	volumeBarWhite.setFillColor(sf::Color(255, 255, 255, uiAlpha));
	volumeText.setFillColor(sf::Color(255, 255, 255, uiAlpha));
	volumeBarWhite.setSize(sf::Vector2f(userVolume * volumeBarWidth, volumeBarHeight));
	diving_music->setVolume(50 * currentVolume * userVolume);
	sea_ambiant->setVolume(80 * currentVolume * userVolume);

	if (state == MainMenuState::Wait)
		return;
	if (state == MainMenuState::Transition1 || state == MainMenuState::Transition2) {
		transitionTime += elapsed.asSeconds();
		uiAlpha -= elapsed.asSeconds() * 255 / uiFadeTime;
		if (uiAlpha < 0)
			uiAlpha = 0;
		playText.setFillColor(sf::Color(255, 255, 255, uiAlpha));
		playText.setOutlineColor(sf::Color(0, 0, 0, uiAlpha));
		playerAnimator->setRotation(70 * easeInOutQuad(transitionTime / transitionDuration));
		backgroundSpriteRect.top = (int)((backgroundSpriteRect.height - backgroundHeightProportion) * (transitionTime / transitionDuration) * (transitionTime / transitionDuration));
		background.setTextureRect(backgroundSpriteRect);
		if (state == MainMenuState::Transition1) {
			if (transitionTime >= startFadeTime) {
				state = MainMenuState::Transition2;
				fader->fadeOut(transitionDuration - startFadeTime);
			}
		}
		else
		{
			if (fader->getState() == FaderState::Sleep)
				state = MainMenuState::Transition3;
		}
	}
	if (state == MainMenuState::Transition3) {
		transitionTime += elapsed.asSeconds();
		currentVolume -= elapsed.asSeconds();
		if (currentVolume <= 0)
			state = MainMenuState::TransitionFinished;
	}
	
	
}

/**
 * Display the main menu.
 *
 * @param window on which the main menu is drawn.
 */
void MainMenu::display(sf::RenderWindow& window) const
{
	window.draw(background);
	playerAnimator->display(window);
	window.draw(gameName);
	window.draw(playText);
	
	window.draw(volumeBar);
	window.draw(volumeBarWhite);
	window.draw(volumeText);
}

/**
 * Function handling clics on the main menu, starting the transition to the game when the user clics on play.
 *
 * @param x position of the clic.
 * @param y position of the clic.
 */

void MainMenu::mousePressed(int x, int y)
{
	if (!(state == MainMenuState::Wait))
		return;
	if (playText.getGlobalBounds().contains(sf::Vector2f(x, y))) {
		state = MainMenuState::Transition1;
		diving_music->play();
	}
}


/**
 * Get the state of the main menu.
 * 
 * @return state of the main menu
 */
MainMenuState MainMenu::getState() const
{
	return state;
}

/**
 * Update the music volume when the user's left mouse button is held.
 *
 * @param pos positioin of the mouse on the window.
 */
void MainMenu::updateVolume(sf::Vector2i pos)
{
	if (!(state == MainMenuState::Wait))
		return;
	if (volumeMouseBox.contains(sf::Vector2f(pos.x, pos.y))) {
		if (pos.x < volumeBarX)
			userVolume = 0;
		else if (pos.x > volumeBarX + volumeBarWidth)
			userVolume = 1;
		else
			userVolume = (pos.x - volumeBarX) / volumeBarWidth;
	}
}

/**
 * Get the volume of the music the user chose.
 *
 * @return volume of the music.
 */
float MainMenu::getUserVolume()
{
	return userVolume;
}

/**
 * Set the value of the user volume.
 *
 * @param volume of the music.
 */
void MainMenu::setUserVolume(float volume)
{
	userVolume = volume;
}


