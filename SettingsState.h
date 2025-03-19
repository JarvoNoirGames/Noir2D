#pragma once
#include "State.hpp"
#include "Engine.h"

namespace Noir2D
{
    class SettingsState : public State {
    public:
        SettingsState(Engine& engine);
        void Init() override;
        void HandleInput() override;
        void Update(float dt) override;
        void Render(float dt) override;
        void Cleanup() override;

    private:
        Engine& _engine;
        sf::Font _font;
        sf::Text _title; 
        sf::Text _fullscreenButton; 
        sf::Text _backButton;

        bool _fullscreen;
    };
}