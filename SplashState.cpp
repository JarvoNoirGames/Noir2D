#include <sstream>
#include <iostream>
#include "SplashState.h"
#include "DEFINITIONS.h"
#include "MainMenuState.h"

namespace Noir2D
{
	SplashState::SplashState(GameDataRef data) : _data(data)
	{

	}

	void SplashState::Init()
	{
		this->_data->Assets.LoadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH);

		_background.setTexture(this->_data->Assets.GetTexture("Splash State Background"));
		sf::Vector2 win = this->_data->Window.getSize();
		sf::Vector2 tex = _background.getTexture()->getSize();
		_background.setPosition((win.x - tex.x) /2,(win.y - tex.y)/2);
	}

	void SplashState::HandleInput()
	{
		sf::Event event;

		while (this->_data->Window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->Window.close();
			}
		}
	}

	void SplashState::Update(float dt)
	{
		if (this->_clock.getElapsedTime().asSeconds() > 3)
		{
			// Switch To Main Menu
			this->_data->Machine.AddState(StateRef(new MainMenuState(_data)),true);
		}
	}

	void SplashState::Draw(float dt)
	{
		this->_data->Window.clear(sf::Color::Black);

		this->_data->Window.draw(this->_background);

		this->_data->Window.display();
	}
}