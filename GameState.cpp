#include "GameState.h"
#include "PauseState.h"
#include "SettingsState.h"

namespace Noir2D
{
    GameState::GameState(Engine& engine) : _engine(engine) {}

    void GameState::Init() 
    {
        _font = AssetManager::GetInstance().GetFont("default");

        _title.setFont(_font);
        _title.setString("Game State");
        _title.setCharacterSize(50);
        _title.setPosition(300, 100);
    }

    void GameState::HandleEvent(const sf::Event& event)
    {
    }

    void GameState::HandleInput() {
        InputManager& input = InputManager::GetInstance();
        if (input.IsKeyPressed(sf::Keyboard::Escape)) 
        {
            _engine.GetStateMachine().PushState(std::make_unique<PauseState>(_engine));
        }

        if (InputManager::GetInstance().IsKeyPressed(sf::Keyboard::S))
        {
            _engine.GetStateMachine().PushState(std::make_unique<SettingsState>(_engine));
        }
    }

    void GameState::Update(float deltaTime) {

    }

    void GameState::Render(float deltaTime) {
        sf::RenderWindow& window = _engine.GetWindow();
        window.draw(_title);
    }

    void GameState::Cleanup() 
    {
        _font = sf::Font();
    }
}