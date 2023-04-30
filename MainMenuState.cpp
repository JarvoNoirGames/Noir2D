#include "MainMenuState.h"
#include "DEFINITIONS.h"
#include <iostream>
#include <sstream>
#include "GameState.h"

namespace Noir2D
{
	MainMenuState::MainMenuState(GameDataRef data) : _data(data)
	{

	}

	void MainMenuState::Init()
	{
		//load textures for menu objects into Assets
		this->_data->Assets.LoadTexture("Background", MAIN_MENU_BACKGROUND_FILEPATH);
		this->_data->Assets.LoadTexture("Title", MAIN_MENU_TITLE_FILEPATH);
		this->_data->Assets.LoadTexture("PlayButton", MAIN_MENU_PLAY_BUTTON);
		this->_data->Assets.LoadTexture("PlayButtonOuter", MAIN_MENU_PLAY_BUTTON_OUTER);

		//retrieve textures from Assets for each object
		this->_background.setTexture(this->_data->Assets.GetTexture("Background"));
		this->_title.setTexture(this->_data->Assets.GetTexture("Title"));
		this->_playButton.setTexture(this->_data->Assets.GetTexture("PlayButton"));
		this->_playButtonOuter.setTexture(this->_data->Assets.GetTexture("PlayButtonOuter"));

		//set positions for objects on screen
		this->_title.setPosition((SCREEN_WIDTH / 2) - this->_title.getGlobalBounds().width/2, (SCREEN_HEIGHT / 2) - this->_title.getGlobalBounds().height / 2);
		this->_playButton.setPosition((SCREEN_WIDTH / 2) - this->_playButton.getGlobalBounds().width/2, (SCREEN_HEIGHT / 2) - this->_playButton.getGlobalBounds().height / 2);
		this->_playButtonOuter.setPosition((SCREEN_WIDTH / 2) - this->_playButtonOuter.getGlobalBounds().width/2, this->_playButtonOuter.getGlobalBounds().height * 0.1);
	}

	void MainMenuState::HandleInput()
	{
		sf::Event event;

		while (this->_data->Window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->Window.close();
			}

			if (this->_data->Input.isSpriteClicked(this->_playButton, sf::Mouse::Left, this->_data->Window))
			{
				// Switch To Game
				this->_data->Machine.AddState(StateRef(new GameState(_data)), true);
			}
		}
	}

	void MainMenuState::Update(float dt)
	{

	}

	void MainMenuState::Draw(float dt)
	{
		//clear last frame
		this->_data->Window.clear();

		//draw all sprites
		this->_data->Window.draw(this->_background);
		this->_data->Window.draw(this->_title);
		this->_data->Window.draw(this->_playButton);
		this->_data->Window.draw(this->_playButtonOuter);

		//display frame
		this->_data->Window.display();
	}
}