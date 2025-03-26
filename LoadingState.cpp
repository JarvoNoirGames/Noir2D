#include "LoadingState.h"
#include "GameState.h"
#include <thread>
#include <chrono>

namespace Noir2D
{
    LoadingState::LoadingState(Engine& engine) : _engine(engine), _progress(0.f) {}

    void LoadingState::Init() {
        _font = AssetManager::GetInstance().GetFont("default");

        _loadingText.setFont(_font);
        _loadingText.setString("Loading...");
        _loadingText.setCharacterSize(40);
        _loadingText.setPosition(350, 200);

        _progressBar.setSize(sf::Vector2f(0, 30));
        _progressBar.setFillColor(sf::Color::Green);
        _progressBar.setPosition(200, 300);
    }

    void LoadingState::HandleEvent(const sf::Event& event)
    {
    }

    void LoadingState::HandleInput() {
        // No input in loading state; this can be enhanced if needed.
    }

    void LoadingState::Update(float dt) {
        // Simulate loading process (use real asset loading in a real game)
        _progress += dt * 0.1f;  // Increase progress over time
        _progressBar.setSize(sf::Vector2f(_progress * 600.f, 30));  // Width is progress

        // When loading is complete, switch to the game state
        if (_progress >= 1.f) {
            _engine.GetStateMachine().ChangeState(std::make_unique<GameState>(_engine));
        }
    }

    void LoadingState::Render(float deltaTime) {
        sf::RenderWindow& window = _engine.GetWindow();
        window.draw(_loadingText);
        window.draw(_progressBar);
    }

    void LoadingState::Cleanup() {
        _font = sf::Font();
    }
}