#pragma once

#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include "InputManager.h"
#include "StateMachine.h"
#include "DEFINITIONS.h"

namespace Noir2D
{
	class Engine {
	public:
		Engine(int width, int height, const std::string& title);
		void Run();
		sf::RenderWindow& GetWindow();
		StateMachine& GetStateMachine();
	private:
		sf::RenderWindow _window;
		StateMachine _stateMachine;
		AssetManager& _assetManager;
		InputManager& _inputManager;

		void ProcessEvents();
		void Update(float deltaTime);
		void Render(float deltaTime);
	};
}