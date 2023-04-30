#include "PauseState.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "DEFINITIONS.h"
#include <iostream>
#include <sstream>
namespace Noir2D
{
	PauseState::PauseState(GameDataRef data) : _data(data)
	{

	}

	void PauseState::Init()
	{
		//load textures for menu objects into Assets
		this->_data->Assets.LoadTexture("PauseBackground", PAUSE_BACKGROUND_FILEPATH);
		this->_data->Assets.LoadTexture("HomeButton", HOME_BUTTON);
		this->_data->Assets.LoadTexture("ResumeButton", RESUME_BUTTON);

		//retrieve textures from Assets for each object
		this->_background.setTexture(this->_data->Assets.GetTexture("PauseBackground"));
		this->_homeButton.setTexture(this->_data->Assets.GetTexture("HomeButton"));
		this->_resumeButton.setTexture(this->_data->Assets.GetTexture("ResumeButton"));

		//set positions for objects on screen
		this->_homeButton.setPosition((this->_data->Window.getSize().x / 2) - (this->_homeButton.getLocalBounds().width / 2), (this->_data->Window.getSize().y / 3) - (this->_homeButton.getLocalBounds().height / 2));
		this->_resumeButton.setPosition((this->_data->Window.getSize().x / 2) - (this->_resumeButton.getLocalBounds().width / 2), (this->_data->Window.getSize().y / 3 * 2) - (this->_resumeButton.getLocalBounds().height / 2));
	}

	void PauseState::HandleInput()
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

			if (this->_data->Input.isSpriteClicked(this->_resumeButton, sf::Mouse::Left, this->_data->Window))
			{
				// Switch To Game
				this->_data->Machine.RemoveState();
			}
		}
	}

	void PauseState::Update(float dt)
	{

	}

	void PauseState::Draw(float dt)
	{
		//clear last frame
		this->_data->Window.clear();

		//draw all sprites
		this->_data->Window.draw(this->_background);
		this->_data->Window.draw(this->_homeButton);
		this->_data->Window.draw(this->_resumeButton);

		//display frame
		this->_data->Window.display();
	}
}