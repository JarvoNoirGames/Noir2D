#pragma once

#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include "InputManager.h"
#include "StateMachine.h"

namespace Noir2D
{
	class Engine {
	public:
		Engine(int width, int height, const std::string& title);
		void Run();

	private:
		sf::RenderWindow window;
		StateMachine stateMachine;
		AssetManager& assetManager;
		InputManager& inputManager;

		void ProcessEvents();
		void Update(float deltaTime);
		void Render(float deltaTime);
	};
}