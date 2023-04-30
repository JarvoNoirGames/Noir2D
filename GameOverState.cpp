#include "GameOverState.h"
#include "PauseState.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "DEFINITIONS.h"
#include <iostream>
#include <sstream>
namespace Noir2D
{
	GameOverState::GameOverState(GameDataRef data) : _data(data)
	{

	}

	void GameOverState::Init()
	{
		//load textures for menu objects into Assets
		this->_data->Assets.LoadTexture("PauseBackground", PAUSE_BACKGROUND_FILEPATH);
		this->_data->Assets.LoadTexture("HomeButton", HOME_BUTTON);
		this->_data->Assets.LoadTexture("RetryButton", RETRY_BUTTON);

		//retrieve textures from Assets for each object
		this->_background.setTexture(this->_data->Assets.GetTexture("PauseBackground"));
		this->_homeButton.setTexture(this->_data->Assets.GetTexture("HomeButton"));
		this->_retryButton.setTexture(this->_data->Assets.GetTexture("RetryButton"));

		//set positions for objects on screen
		this->_homeButton.setPosition((this->_data->Window.getSize().x / 2) - (this->_homeButton.getLocalBounds().width / 2), (this->_data->Window.getSize().y / 3 * 2) - (this->_homeButton.getLocalBounds().height / 2));
		this->_retryButton.setPosition((this->_data->Window.getSize().x / 2) - (this->_retryButton.getLocalBounds().width / 2), (this->_data->Window.getSize().y / 3 ) - (this->_retryButton.getLocalBounds().height / 2));
	}

	void GameOverState::HandleInput()
	{
		sf::Event event;

		while (this->_data->Window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->Window.close();
			}

			if (this->_data->Input.isSpriteClicked(this->_homeButton, sf::Mouse::Left, this->_data->Window))
			{
				//remove current state
				this->_data->Machine.RemoveState();

				// Switch To MainMenu
				this->_data->Machine.AddState(StateRef(new MainMenuState(_data)), true);
			}

			if (this->_data->Input.isSpriteClicked(this->_retryButton, sf::Mouse::Left, this->_data->Window))
			{
				// Switch To Game
				this->_data->Machine.AddState(StateRef(new GameState(_data)), true);
			}
		}
	}

	void GameOverState::Update(float dt)
	{

	}

	void GameOverState::Draw(float dt)
	{
		//clear last frame
		this->_data->Window.clear(sf::Color::Black);

		//draw all sprites
		this->_data->Window.draw(this->_homeButton);
		this->_data->Window.draw(this->_retryButton);

		//display frame
		this->_data->Window.display();
	}
}