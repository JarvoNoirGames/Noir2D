#pragma once
#include "State.hpp"
#include "Engine.h"

namespace Noir2D
{
    class LoadingState : public State {
    public:
        LoadingState(Engine& engine);
        void Init() override;
        void HandleInput() override;
        void Update(float dt) override;
        void Render(float dt) override;
        void Cleanup() override;

    private:
        Engine& _engine;
        sf::Font _font;
        sf::Text _loadingText;
        sf::RectangleShape _progressBar;
        float _progress;
    };
}