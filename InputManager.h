#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <functional>
#include <string>
#include <vector>

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

        // Gamepad Queries
        bool IsGamepadButtonPressed(unsigned int joystickId, unsigned int button) const;
        bool WasGamepadButtonReleased(unsigned int joystickId, unsigned int button) const;
        float GetGamepadAxis(unsigned int joystickId, sf::Joystick::Axis axis) const; // deadzone-applied, -100..100

        // Action Mapping
        void BindActionKey(const std::string& action, sf::Keyboard::Key key);
        void BindActionGamepadButton(const std::string& action, unsigned int button, unsigned int joystickId = 0);
        bool IsActionPressed(const std::string& action) const;

        void BindAxisKeys(const std::string& axisName, sf::Keyboard::Key negativeKey, sf::Keyboard::Key positiveKey);
        void BindAxisGamepad(const std::string& axisName, sf::Joystick::Axis axis, unsigned int joystickId = 0);
        float GetActionAxis(const std::string& axisName) const; // -1..1

        // Event Processing
        void ProcessEvent(const sf::Event& event);
        void Update();  // Resets "released" states once per frame

        // Callback Bindings
        void BindKeyPress(sf::Keyboard::Key key, std::function<void()> callback);
        void BindKeyRelease(sf::Keyboard::Key key, std::function<void()> callback);

    private:
        InputManager() = default;  // Private constructor (Singleton)

        static unsigned int MakeGamepadKey(unsigned int joystickId, unsigned int button);
        static constexpr float DEADZONE = 15.f; // percent — ignores stick drift near center

        std::unordered_map<sf::Keyboard::Key, bool> keyStates;
        std::unordered_map<sf::Keyboard::Key, bool> keyReleasedStates;

        std::unordered_map<sf::Mouse::Button, bool> mouseStates;
        std::unordered_map<sf::Mouse::Button, bool> mouseReleasedStates;

        std::unordered_map<unsigned int, bool> gamepadStates;
        std::unordered_map<unsigned int, bool> gamepadReleasedStates;

        std::unordered_map<sf::Keyboard::Key, std::function<void()>> keyPressCallbacks;
        std::unordered_map<sf::Keyboard::Key, std::function<void()>> keyReleaseCallbacks;

        struct ActionBinding
        {
            std::vector<sf::Keyboard::Key> keys;
            std::vector<std::pair<unsigned int, unsigned int>> gamepadButtons; // {joystickId, button}
        };
        std::unordered_map<std::string, ActionBinding> actionBindings;

        struct AxisBinding
        {
            bool hasKeyboard = false;
            sf::Keyboard::Key negativeKey = sf::Keyboard::Unknown;
            sf::Keyboard::Key positiveKey = sf::Keyboard::Unknown;

            bool hasGamepad = false;
            unsigned int joystickId = 0;
            sf::Joystick::Axis gamepadAxis = sf::Joystick::X;
        };
        std::unordered_map<std::string, AxisBinding> axisBindings;
    };
}