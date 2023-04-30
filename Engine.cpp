#include "Engine.h"
#include "SplashState.h"
#include <iostream>
namespace Noir2D
{
	Engine::Engine(int w, int h, std::string title)
	{
		Data->Window.create(sf::VideoMode(w, h), title);

		//set window icon
		auto image = sf::Image{};
		if (!image.loadFromFile("Resources/res/JNWhite.png"))
		{
			//replace this with proper error handling
			std::cout << "ERROR";
		}
		Data->Window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
		
		//set state to splash screen
		Data->Machine.AddState(StateRef(new SplashState(this->Data)));
		this->Run();
	}

	void Engine::Run()
	{
		float newTime;
		float frameTime;
		float interpolation;
		float currentTime = this->_clock.getElapsedTime().asSeconds();
		float accumalator = 0.0f;

		while (this->Data->Window.isOpen())
		{
			this->Data->Machine.ProcessStateChanges();

			newTime = this->_clock.getElapsedTime().asSeconds();
			frameTime = newTime - currentTime;

			if (frameTime > 0.25f)
			{
				frameTime = 0.25f;
			}

			currentTime = newTime;
			accumalator += frameTime;

			while (accumalator >= _dt)
			{
				this->Data->Machine.GetActiveState()->HandleInput();
				this->Data->Machine.GetActiveState()->Update(_dt);
				accumalator -= _dt;
			}

			interpolation = accumalator / _dt;
			this->Data->Machine.GetActiveState()->Draw(interpolation);
		}
	}
}