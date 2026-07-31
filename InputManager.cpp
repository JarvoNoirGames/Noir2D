#include "InputManager.h"

namespace Noir2D
{
    // Singleton Instance
    InputManager& InputManager::GetInstance() {
        static InputManager instance;
        return instance;
    }

    // Keyboard Handling
    bool InputManager::IsKeyPressed(sf::Keyboard::Key key) const {
        auto it = keyStates.find(key);
        return it != keyStates.end() && it->second;
    }

    bool InputManager::WasKeyReleased(sf::Keyboard::Key key) const {
        auto it = keyReleasedStates.find(key);
        return it != keyReleasedStates.end() && it->second;
    }

    // Mouse Handling
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

    // Event Processing
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

    // Frame Update (Reset Released States)
    void InputManager::Update() {
        sf::Joystick::update();
        keyReleasedStates.clear();
        mouseReleasedStates.clear();
    }

    // Key Binding
    void InputManager::BindKeyPress(sf::Keyboard::Key key, std::function<void()> callback) {
        keyPressCallbacks[key] = std::move(callback);
    }

    void InputManager::BindKeyRelease(sf::Keyboard::Key key, std::function<void()> callback) {
        keyReleaseCallbacks[key] = std::move(callback);
    }

    bool InputManager::IsGamepadButtonPressed(unsigned int joystickId, unsigned int button) const
    {
        return sf::Joystick::isConnected(joystickId) && sf::Joystick::isButtonPressed(joystickId, button);
    }

    float InputManager::GetGamepadAxis(unsigned int joystickId, sf::Joystick::Axis axis) const
    {
        if (!sf::Joystick::isConnected(joystickId))
            return 0.f;

        float raw = sf::Joystick::getAxisPosition(joystickId, axis);
        if (std::abs(raw) < DEADZONE)
            return 0.f;

        return raw; // -100..100
    }

    void InputManager::BindActionKey(const std::string& action, sf::Keyboard::Key key)
    {
        actionBindings[action].keys.push_back(key);
    }

    void InputManager::BindActionGamepadButton(const std::string& action, unsigned int button, unsigned int joystickId)
    {
        actionBindings[action].gamepadButtons.push_back({ joystickId, button });
    }

    bool InputManager::IsActionPressed(const std::string& action) const
    {
        auto it = actionBindings.find(action);
        if (it == actionBindings.end())
            return false; // unbound action — fails safe, doesn't crash

        for (auto key : it->second.keys)
            if (IsKeyPressed(key)) return true;

        for (auto& pair : it->second.gamepadButtons)
            if (IsGamepadButtonPressed(pair.first, pair.second)) return true;

        return false;
    }

    void InputManager::BindAxisKeys(const std::string& axisName, sf::Keyboard::Key negativeKey, sf::Keyboard::Key positiveKey)
    {
        auto& binding = axisBindings[axisName];
        binding.hasKeyboard = true;
        binding.negativeKey = negativeKey;
        binding.positiveKey = positiveKey;
    }

    void InputManager::BindAxisGamepad(const std::string& axisName, sf::Joystick::Axis axis, unsigned int joystickId)
    {
        auto& binding = axisBindings[axisName];
        binding.hasGamepad = true;
        binding.joystickId = joystickId;
        binding.gamepadAxis = axis;
    }

    float InputManager::GetActionAxis(const std::string& axisName) const
    {
        auto it = axisBindings.find(axisName);
        if (it == axisBindings.end())
            return 0.f;

        float value = 0.f;

        if (it->second.hasKeyboard)
        {
            if (IsKeyPressed(it->second.negativeKey)) value -= 1.f;
            if (IsKeyPressed(it->second.positiveKey)) value += 1.f;
        }

        if (it->second.hasGamepad)
        {
            float gamepadValue = GetGamepadAxis(it->second.joystickId, it->second.gamepadAxis) / 100.f;
            if (std::abs(gamepadValue) > std::abs(value))
                value = gamepadValue; // whichever device is being pushed harder wins
        }

        return value;
    }
}