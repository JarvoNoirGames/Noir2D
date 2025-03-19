#pragma once
#include "State.hpp"
#include "Engine.h"
#include <SFML/Graphics.hpp>

namespace Noir2D
{
	class SplashScreenState : public State
	{
	public:
		SplashScreenState(Engine& engine);
		void Init() override;
		void HandleInput() override;
		void Update(float deltaTime) override;
		void Render(float deltaTime) override;
		void Cleanup() override;
	private:
		Engine& _engine;
		sf::Texture _logoTexture;
		sf::Sprite _logoSprite;
		sf::Clock _clock;  // Timer for the splash screen
		float _displayTime = 3.0f;  // Time in seconds before transitioning
	};
}
