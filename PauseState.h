#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Engine.h"
namespace Noir2D
{
	class PauseState : public State
	{
	public:
		PauseState(GameDataRef data);
		~PauseState();

		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
	private:
		GameDataRef _data;
		sf::Sprite _background;
		sf::Sprite _homeButton;
		sf::Sprite _resumeButton;
	};
}
