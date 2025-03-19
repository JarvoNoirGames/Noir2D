#include "Engine.h"
#include "SplashScreenState.h"
#include <iostream>
namespace Noir2D
{
    Engine::Engine(int width, int height, const std::string& title)
        : _window(sf::VideoMode(width, height), title),
        _assetManager(AssetManager::GetInstance()),
        _inputManager(InputManager::GetInstance()) 
    {
        AssetManager::GetInstance().LoadTexture("splash_logo", SPLASH_SCENE_BACKGROUND_FILEPATH);
        AssetManager::GetInstance().LoadFont("default", DEFAULT_FONT);
        _stateMachine.PushState(std::make_unique<SplashScreenState>(*this));
    }

    void Engine::Run() {
        sf::Clock clock;
        while (_window.isOpen()) {
            float dt = clock.restart().asSeconds();
            ProcessEvents();
            Update(dt);
            Render(dt);
        }
        _stateMachine.Cleanup();
        AssetManager::GetInstance().Cleanup();
    }

    sf::RenderWindow& Engine::GetWindow()
    {
        return _window;
    }

    StateMachine& Engine::GetStateMachine()
    {
        return _stateMachine;
    }

    void Engine::ProcessEvents() {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            {
                _window.close();
            }
            _inputManager.ProcessEvent(event);
        }
        // Forward input handling to the current state
        if (!_stateMachine.IsEmpty()) {
            _stateMachine.GetActiveState()->HandleInput();
        }
    }

    void Engine::Update(float deltaTime) {
        _inputManager.Update();  // Reset input states
        if (_stateMachine.GetActiveState()) _stateMachine.GetActiveState()->Update(deltaTime);
    }

    void Engine::Render(float deltaTime) {
        _window.clear(sf::Color::Black);
        if (_stateMachine.GetActiveState()) _stateMachine.GetActiveState()->Render(deltaTime);
        _window.display();
    }
}