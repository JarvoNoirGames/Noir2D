#pragma once
#include "State.hpp"
#include "Engine.h"
#include "GUI.h"
#include "GUIDropdown.h"
#include "GUIButton.h"
#include <SFML/Graphics.hpp>

namespace Noir2D
{
	class MainMenuState : public State
	{
    public:
        MainMenuState(Engine& engine);
        void Init() override;
        void HandleEvent(const sf::Event& event) override;
        void HandleInput() override;
        void Update(float dt) override;
        void Render(float dt) override;
        void Cleanup() override;
        void StartButtonOnClick();
        void QuitButtonOnClick();
        void SettingsButtonOnClick();
    private:
        Engine& _engine;
        sf::Font _font;
        sf::Text _title;
        sf::Text _playButton;
        sf::Text _exitButton;
        GUI _gui;
	};
}
