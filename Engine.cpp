#include "Engine.h"
#include "SplashScreenState.h"
#include <iostream>
namespace Noir2D
{
    Engine::Engine(int width, int height, const std::string& title, bool fullscreen)
        : _window(fullscreen ? sf::VideoMode::getDesktopMode() : sf::VideoMode(width, height),
            title,
            fullscreen ? sf::Style::Fullscreen : sf::Style::Default),
        _assetManager(AssetManager::GetInstance()),
        _inputManager(InputManager::GetInstance()) ,
        _audioManager(AudioManager::GetInstance())
    {
        AssetManager::GetInstance().LoadTexture("splash_logo", SPLASH_SCENE_BACKGROUND_FILEPATH);
        AssetManager::GetInstance().LoadFont("default", DEFAULT_FONT);
        ResolutionManager::GetInstance().SetBaseResolution({ SCREEN_WIDTH, SCREEN_HEIGHT });
        ResolutionManager::GetInstance().SetWindowSize(_window.getSize());
        _stateMachine.PushState(std::make_unique<SplashScreenState>(*this));
    }

    void Engine::Run() {
        sf::Clock clock;
        _window.setFramerateLimit(60);
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

    void Engine::RequestStateChange(std::unique_ptr<State> newState)
    {
        _pendingState = std::move(newState);
    }

    void Engine::RequestQuit()
    {
        _quitRequested = true;
    }

    void Engine::ProcessEvents() {
        _inputManager.Update(); // reset last frame's "released" flags first

        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window.close();

            _inputManager.ProcessEvent(event);

            if (!_stateMachine.IsEmpty())
                _stateMachine.GetActiveState()->HandleEvent(event);
        }

        if (_quitRequested)
            _window.close();

        if (!_stateMachine.IsEmpty())
            _stateMachine.GetActiveState()->HandleInput();

        if (_pendingState) {
            _stateMachine.ChangeState(std::move(_pendingState));
            _pendingState.reset();
        }
    }

    void Engine::Update(float deltaTime) {
        if (_stateMachine.GetActiveState()) _stateMachine.GetActiveState()->Update(deltaTime);
        _audioManager.Update();
    }

    void Engine::Render(float deltaTime) {
        _window.clear(sf::Color::Black);
        if (_stateMachine.GetActiveState()) _stateMachine.GetActiveState()->Render(deltaTime);
        _window.display();
    }
}