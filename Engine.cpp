#include "Engine.h"
#include <iostream>
namespace Noir2D
{
    Engine::Engine(int width, int height, const std::string& title)
        : window(sf::VideoMode(width, height), title),
        assetManager(AssetManager::GetInstance()),
        inputManager(InputManager::GetInstance()) {}

    void Engine::Run() {
        sf::Clock clock;
        while (window.isOpen()) {
            float dt = clock.restart().asSeconds();
            ProcessEvents();
            Update(dt);
            Render(dt);
        }
    }

    void Engine::ProcessEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            inputManager.ProcessEvent(event);
            if (event.type == sf::Event::Closed) window.close();
        }
    }

    void Engine::Update(float deltaTime) {
        inputManager.Update();  // Reset input states
        if (stateMachine.GetActiveState()) stateMachine.GetActiveState()->Update(deltaTime);
    }

    void Engine::Render(float deltaTime) {
        window.clear(sf::Color::Blue);
        if (stateMachine.GetActiveState()) stateMachine.GetActiveState()->Render(deltaTime);
        window.display();
    }
}