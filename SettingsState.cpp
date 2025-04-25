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

        auto fullscreenButton = std::make_shared<GUIButton>(
            sf::Vector2f(350, 250), sf::Vector2f(200, 50), _font, "Fullscreen",
            [this]() {sf::Vector2f(400, 300), this->ToggleFullscreen(); }
        );
        auto backButton = std::make_shared<GUIButton>(
            sf::Vector2f(350, 450), sf::Vector2f(200, 50), _font, "Back",
            [this]() {sf::Vector2f(400, 300), ReturnToMainMenu(); }
        );

        _gui.AddElement(fullscreenButton);
        _gui.AddElement(backButton);
    }

    void SettingsState::HandleEvent(const sf::Event& event)
    {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(_engine.GetWindow());
        sf::Vector2f worldPos = _engine.GetWindow().mapPixelToCoords(pixelPos);
        _gui.HandleEvent(event,worldPos);
    }

    void SettingsState::HandleInput() 
    {
        InputManager& input = InputManager::GetInstance();
    }

    void SettingsState::Update(float deltaTime) 
    {

    }

    void SettingsState::Render(float deltaTime) 
    {
        sf::RenderWindow& window = _engine.GetWindow();
        window.draw(_title);
        window.draw(_fullscreenButton);
        window.draw(_backButton);
        _gui.Draw(window);  
    }

    void SettingsState::Cleanup() {
        _font = sf::Font();
        //these will be replaced by GUI buttons soon
        _fullscreenButton = sf::Text();
        _backButton = sf::Text();
    }
    void SettingsState::ToggleFullscreen()
    {
        _fullscreen = !_fullscreen;
        if (_fullscreen) 
        {
            _engine.GetWindow().create(sf::VideoMode(1920, 1080), "NOIR2D", sf::Style::Fullscreen);
            ResolutionManager::GetInstance().SetWindowSize(_engine.GetWindow().getSize());
            _gui.UpdateLayout();
        }
        else 
        {
            _engine.GetWindow().create(sf::VideoMode(800, 600), "NOIR2D");
            ResolutionManager::GetInstance().SetWindowSize(_engine.GetWindow().getSize());
            _gui.UpdateLayout();
        }
    }
    void SettingsState::ReturnToMainMenu()
    {
        if (!_engine.GetStateMachine().IsEmpty()) 
        {
            _engine.RequestStateChange(std::make_unique<MainMenuState>(_engine));
        }
    }
}