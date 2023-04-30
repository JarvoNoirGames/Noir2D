#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Engine.h"
namespace Noir2D
{
	class MainMenuState : public State
	{
	public:
		MainMenuState(GameDataRef Data);
		~MainMenuState();

		void Init();

		// No pause() or resume() methods here as this
		// is a very simple example of a game state.

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;
		sf::Sprite _background;
		sf::Sprite _title;
		sf::Sprite _playButton;
		sf::Sprite _playButtonOuter;
	};
}
