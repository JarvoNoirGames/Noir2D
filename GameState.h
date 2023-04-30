#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Engine.h"

namespace Noir2D
{
	class GameState : public State
	{
	public:
		GameState(GameDataRef Data);
		~GameState();

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
		sf::Sprite _pauseButton;
		
		int _turn;
		int _gameState;
	};
}
