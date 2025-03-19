#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <functional>

namespace Noir2D {
    class InputManager {
    public:
        static InputManager& GetInstance();  // Singleton pattern

        // Key and Mouse Queries
        bool IsKeyPressed(sf::Keyboard::Key key) const;
        bool WasKeyReleased(sf::Keyboard::Key key) const;

        bool IsMouseButtonPressed(sf::Mouse::Button button) const;
        bool WasMouseButtonReleased(sf::Mouse::Button button) const;
        sf::Vector2i GetMousePosition(const sf::RenderWindow& window) const;

        // Event Processing
        void ProcessEvent(const sf::Event& event);
        void Update();  // Resets "released" states once per frame

        // Callback Bindings
        void BindKeyPress(sf::Keyboard::Key key, std::function<void()> callback);
        void BindKeyRelease(sf::Keyboard::Key key, std::function<void()> callback);

    private:
        InputManager() = default;  // Private constructor (Singleton)

        std::unordered_map<sf::Keyboard::Key, bool> keyStates;
        std::unordered_map<sf::Keyboard::Key, bool> keyReleasedStates;

        std::unordered_map<sf::Mouse::Button, bool> mouseStates;
        std::unordered_map<sf::Mouse::Button, bool> mouseReleasedStates;

        std::unordered_map<sf::Keyboard::Key, std::function<void()>> keyPressCallbacks;
        std::unordered_map<sf::Keyboard::Key, std::function<void()>> keyReleaseCallbacks;
    };
}
