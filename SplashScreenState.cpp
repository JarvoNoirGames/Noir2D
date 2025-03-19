#include "SplashScreenState.h"
#include "MainMenuState.h"

namespace Noir2D
{
    SplashScreenState::SplashScreenState(Engine& engine) : _engine(engine) {}

    void SplashScreenState::Init() {
        // Load the splash screen logo
        _logoTexture = AssetManager::GetInstance().GetTexture("splash_logo");
        _logoSprite.setTexture(_logoTexture);

        // Center the logo in the window
        sf::Vector2u windowSize = _engine.GetWindow().getSize();
        sf::Vector2u textureSize = _logoTexture.getSize();
        _logoSprite.setPosition((windowSize.x - textureSize.x) / 2, (windowSize.y - textureSize.y) / 2);

        // Start the clock
        _clock.restart();
    }

    void SplashScreenState::HandleInput() {
        InputManager& input = InputManager::GetInstance();

        // Allow skipping splash screen by pressing any key
        if (input.IsKeyPressed(sf::Keyboard::Enter)) {
            _engine.GetStateMachine().ChangeState(std::make_unique<MainMenuState>(_engine));
        }
    }

    void SplashScreenState::Update(float dt) {
        // Automatically transition after `displayTime` seconds
        if (_clock.getElapsedTime().asSeconds() >= _displayTime) {
            _engine.GetStateMachine().ChangeState(std::make_unique<MainMenuState>(_engine));
        }
    }

    void SplashScreenState::Render(float deltaTime) {
        sf::RenderWindow& window = _engine.GetWindow();
        window.draw(_logoSprite);
    }

    void SplashScreenState::Cleanup() {
        // No dynamic memory allocated, so no cleanup needed
    }
}