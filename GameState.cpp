#include "GameState.h"
#include "GameOverState.h"
#include "DEFINITIONS.h"
#include "PauseState.h"
#include <iostream>
#include <sstream>
namespace Noir2D
{
	GameState::GameState(GameDataRef data) : _data(data)
	{
		_gameState = STATE_PLAYING;
		_turn = PLAYER_PIECE;
	}

	void GameState::Init()
	{
		//load textures into Assets
		this->_data->Assets.LoadTexture("PauseButton", GAME_PAUSE_BUTTON);

		//retrieve textures from Assets for each object
		this->_background.setTexture(this->_data->Assets.GetTexture("Background"));
		this->_pauseButton.setTexture(this->_data->Assets.GetTexture("PauseButton"));

		//set positions for objects on screen
		this->_pauseButton.setPosition(this->_data->Window.getSize().x - this->_pauseButton.getLocalBounds().width, this->_data->Window.getPosition().y);
	}

	void GameState::HandleInput()
	{
		sf::Event event;

		while (this->_data->Window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->Window.close();
			}

			if (this->_data->Input.isSpriteClicked(this->_pauseButton, sf::Mouse::Left, this->_data->Window))
			{
				//don't replace game state with pause state, just halt game state for now
				this->_data->Machine.AddState(StateRef(new PauseState(_data)), false);
			}
		}
	}

	void GameState::Update(float dt)
	{

	}

	void GameState::Draw(float dt)
	{
		//clear last frame
		this->_data->Window.clear();

		//draw all sprites
		this->_data->Window.draw(this->_background);
		this->_data->Window.draw(this->_pauseButton);

		//display frame
		this->_data->Window.display();
	}
}