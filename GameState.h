#pragma once
#include "State.hpp"
#include "Engine.h"
#include "GUI.h"
#include "GUIButton.h"

namespace Noir2D
{
	class GameState : public State
	{
    public:
        GameState(Engine& engine);
        void Init() override;
        void HandleEvent(const sf::Event& event) override;
        void HandleInput() override;
        void Update(float dt) override;
        void Render(float dt) override;
        void Cleanup() override;

    private:
        Engine& _engine;
        sf::Text _title;
        sf::Font _font;
        GUI _gui;
	};
}
