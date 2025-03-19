#pragma once
#include "State.hpp"
#include "Engine.h"

namespace Noir2D
{
	class GameState : public State
	{
    public:
        GameState(Engine& engine);
        void Init() override;
        void HandleInput() override;
        void Update(float dt) override;
        void Render(float dt) override;
        void Cleanup() override;

    private:
        Engine& _engine;
	};
}
