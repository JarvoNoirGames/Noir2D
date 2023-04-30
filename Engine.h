#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include "InputManager.h"
#include "StateMachine.h"

namespace Noir2D
{
	struct GameData
	{
		StateMachine Machine;
		sf::RenderWindow Window;
		AssetManager Assets;
		InputManager Input;
	};

	typedef std::shared_ptr<GameData> GameDataRef;

	class Engine
	{
	public:
		Engine(int width, int height, std::string title);

	private:
		const float _dt = 1.0f / 60.0f;
		sf::Clock _clock;
		GameDataRef Data = std::make_shared<GameData>();

		void Run();
	};
}