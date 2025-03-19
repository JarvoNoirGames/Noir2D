#include "InputManager.h"

namespace Noir2D
{
    // Singleton Instance
    InputManager& InputManager::GetInstance() {
        static InputManager instance;
        return instance;
    }

    // --- Keyboard Handling ---
    bool InputManager::IsKeyPressed(sf::Keyboard::Key key) const {
        auto it = keyStates.find(key);
        return it != keyStates.end() && it->second;
    }

    bool InputManager::WasKeyReleased(sf::Keyboard::Key key) const {
        auto it = keyReleasedStates.find(key);
        return it != keyReleasedStates.end() && it->second;
    }

    // --- Mouse Handling ---
    bool InputManager::IsMouseButtonPressed(sf::Mouse::Button button) const {
        auto it = mouseStates.find(button);
        return it != mouseStates.end() && it->second;
    }

    bool InputManager::WasMouseButtonReleased(sf::Mouse::Button button) const {
        auto it = mouseReleasedStates.find(button);
        return it != mouseReleasedStates.end() && it->second;
    }

    sf::Vector2i InputManager::GetMousePosition(const sf::RenderWindow& window) const {
        return sf::Mouse::getPosition(window);
    }

    // --- Event Processing ---
    void InputManager::ProcessEvent(const sf::Event& event) {
        if (event.type == sf::Event::KeyPressed) {
            keyStates[event.key.code] = true;
            keyReleasedStates[event.key.code] = false;

            if (keyPressCallbacks.count(event.key.code)) {
                keyPressCallbacks[event.key.code]();
            }
        }

        if (event.type == sf::Event::KeyReleased) {
            keyStates[event.key.code] = false;
            keyReleasedStates[event.key.code] = true;

            if (keyReleaseCallbacks.count(event.key.code)) {
                keyReleaseCallbacks[event.key.code]();
            }
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            mouseStates[event.mouseButton.button] = true;
            mouseReleasedStates[event.mouseButton.button] = false;
        }

        if (event.type == sf::Event::MouseButtonReleased) {
            mouseStates[event.mouseButton.button] = false;
            mouseReleasedStates[event.mouseButton.button] = true;
        }
    }

    // --- Frame Update (Reset Released States) ---
    void InputManager::Update() {
        keyReleasedStates.clear();
        mouseReleasedStates.clear();
    }

    // --- Key Binding ---
    void InputManager::BindKeyPress(sf::Keyboard::Key key, std::function<void()> callback) {
        keyPressCallbacks[key] = std::move(callback);
    }

    void InputManager::BindKeyRelease(sf::Keyboard::Key key, std::function<void()> callback) {
        keyReleaseCallbacks[key] = std::move(callback);
    }
}