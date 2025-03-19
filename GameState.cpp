#include "GameState.h"
#include "PauseState.h"
#include "SettingsState.h"

namespace Noir2D
{
    GameState::GameState(Engine& engine) : _engine(engine) {}

    void GameState::Init() 
    {

    }

    void GameState::HandleInput() {
        InputManager& input = InputManager::GetInstance();
        if (input.IsKeyPressed(sf::Keyboard::Escape)) {
            _engine.GetStateMachine().PushState(std::make_unique<PauseState>(_engine));
        }

        // Example button handling inside `GameState`'s `HandleInput` method:
        if (InputManager::GetInstance().IsKeyPressed(sf::Keyboard::S))
            _engine.GetStateMachine().PushState(std::make_unique<SettingsState>(_engine));
    }

    void GameState::Update(float deltaTime) {

    }

    void GameState::Render(float deltaTime) {

    }

    void GameState::Cleanup() 
    {

    }
}