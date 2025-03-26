#include "GameOverState.h"
#include "MainMenuState.h"

namespace Noir2D
{
    GameOverState::GameOverState(Engine& engine) : _engine(engine) {}

    void GameOverState::Init() {
        _font = AssetManager::GetInstance().GetFont("default");

        _gameOverText.setFont(_font);
        _gameOverText.setString("Game Over!\nPress Enter to Restart");
        _gameOverText.setCharacterSize(40);
        _gameOverText.setPosition(200, 200);
    }

    void GameOverState::HandleEvent(const sf::Event& event)
    {

    }

    void GameOverState::HandleInput() {
        if (InputManager::GetInstance().IsKeyPressed(sf::Keyboard::Enter)) {
            _engine.GetStateMachine().ChangeState(std::make_unique<MainMenuState>(_engine));
        }
    }

    void GameOverState::Update(float deltaTime) {}

    void GameOverState::Render(float deltaTime) {
        _engine.GetWindow().draw(_gameOverText);
    }

    void GameOverState::Cleanup() 
    {
        _font = sf::Font();
    }
}