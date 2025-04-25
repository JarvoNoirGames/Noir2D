#pragma once
#include "State.hpp"
#include "Engine.h"

namespace Noir2D
{
	class PauseState : public State
	{
	public:
		PauseState(Engine& engine);
		void Init() override;
		void HandleEvent(const sf::Event& event) override;
		void HandleInput() override;
		void Update(float dt) override;
		void Render(float dt) override;
		void Cleanup() override;
	private:
		Engine& _engine;
		sf::Font _font;
		sf::Text _pauseText;
	};
}