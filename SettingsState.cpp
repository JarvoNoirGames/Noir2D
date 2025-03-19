#include "SettingsState.h"
#include "MainMenuState.h"
#include "Engine.h"

namespace Noir2D
{
    SettingsState::SettingsState(Engine& engine) : _engine(engine), _fullscreen(false) {}

    void SettingsState::Init() {
        _font = AssetManager::GetInstance().GetFont("default");

        _title.setFont(_font);
        _title.setString("Settings");
        _title.setCharacterSize(50);
        _title.setPosition(300, 100);

        _fullscreenButton.setFont(_font);
        _fullscreenButton.setString("Fullscreen: OFF");
        _fullscreenButton.setCharacterSize(30);
        _fullscreenButton.setPosition(350, 250);

        _backButton.setFont(_font);
        _backButton.setString("Back");
        _backButton.setCharacterSize(30);
        _backButton.setPosition(350, 350);
    }

    void SettingsState::HandleInput() {
        InputManager& input = InputManager::GetInstance();

        if (input.IsKeyPressed(sf::Keyboard::Enter)) {
            // Toggle fullscreen on Enter key press
            _fullscreen = !_fullscreen;
            if (_fullscreen) {
                _engine.GetWindow().create(sf::VideoMode(1920, 1080), "Game", sf::Style::Fullscreen);
            }
            else {
                _engine.GetWindow().create(sf::VideoMode(800, 600), "Game");
            }
            _fullscreenButton.setString("Fullscreen: " + std::string(_fullscreen ? "ON" : "OFF"));
        }

        if (input.IsKeyPressed(sf::Keyboard::Escape)) {
            _engine.GetStateMachine().PopState();  // Go back to the previous state
        }
    }

    void SettingsState::Update(float deltaTime) {
        // Additional updates if required, like saving preferences
    }

    void SettingsState::Render(float deltaTime) {
        sf::RenderWindow& window = _engine.GetWindow();
        window.draw(_title);
        window.draw(_fullscreenButton);
        window.draw(_backButton);
    }

    void SettingsState::Cleanup() {
        _font = sf::Font();
        //these will be replaced by GUI buttons soon
        _fullscreenButton = sf::Text();
        _backButton = sf::Text();
    }
}