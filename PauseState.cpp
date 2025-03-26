#include "PauseState.h"

namespace Noir2D
{
    PauseState::PauseState(Engine& engine) : _engine(engine) {}

    void PauseState::Init() {
        _font = AssetManager::GetInstance().GetFont("default");

        _pauseText.setFont(_font);
        _pauseText.setString("Paused\nPress ESC to Resume");
        _pauseText.setCharacterSize(40);
        _pauseText.setPosition(200, 200);
    }

    void PauseState::HandleEvent(const sf::Event& event)
    {
    }

    void PauseState::HandleInput() {
        if (InputManager::GetInstance().IsKeyPressed(sf::Keyboard::Escape)) {
            _engine.GetStateMachine().PopState();
        }
    }

    void PauseState::Update(float deltaTime) {}

    void PauseState::Render(float deltaTime) {
        _engine.GetWindow().draw(_pauseText);
    }

    void PauseState::Cleanup()
    {
        _font = sf::Font();
    }
}