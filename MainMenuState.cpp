#include "MainMenuState.h"
#include "GameState.h"
#include "SettingsState.h"
#include <iostream>

namespace Noir2D
{
    MainMenuState::MainMenuState(Engine& engine) : _engine(engine) {}

	void MainMenuState::Init()
	{
        //Main Logo
        const sf::Texture& logoTexture = AssetManager::GetInstance().GetTexture("splash_logo");
        sf::Vector2u windowSize = _engine.GetWindow().getSize();
        sf::Vector2u textureSize = logoTexture.getSize();
        auto logoImage = std::make_shared<GUIImage>(sf::Vector2f((windowSize.x - textureSize.x) / 2, (windowSize.y - textureSize.y) / 2), logoTexture);
        _gui.AddElement(logoImage);

        //Menu Buttons
		_font = AssetManager::GetInstance().GetFont("default");
        std::vector<std::string> buttonLabels = { "Start Game", "Settings", "Quit" };
        std::vector<std::function<void()>> actions = {
            [this]() { StartButtonOnClick(); },
            [this]() { SettingsButtonOnClick(); },
            [this]() { QuitButtonOnClick(); }
        };
        const float buttonWidth = 250.0f;
        const float buttonHeight = 60.0f;
        const float verticalSpacing = 20.0f;
        sf::Vector2f startPosition(275.f, 300.f);

        for (size_t i = 0; i < buttonLabels.size(); ++i) {
            sf::Vector2f position = {
                startPosition.x,
                startPosition.y + (buttonHeight + verticalSpacing) * static_cast<float>(i)
            };
            auto button = std::make_shared<GUIButton>(
                position, sf::Vector2f(buttonWidth, buttonHeight),
                _font, buttonLabels[i], actions[i]
            );
            _gui.AddElement(button);
        }
        _gui.UpdateLayout();
	}

    void MainMenuState::HandleInput()
    {
        InputManager& input = InputManager::GetInstance();
        
        if (input.IsKeyPressed(sf::Keyboard::Escape))
            _engine.GetWindow().close();

        if (input.IsKeyPressed(sf::Keyboard::Enter))
            _engine.GetStateMachine().ChangeState(std::make_unique<GameState>(_engine));
    }

    void MainMenuState::Update(float deltaTime)
    {
        _gui.Update(deltaTime);
    }

    void MainMenuState::Render(float deltaTime)
    {
        sf::RenderWindow& window = _engine.GetWindow();
        _gui.Draw(window);
    }

    void MainMenuState::Cleanup() 
    {
        _font = sf::Font();
    }
    void MainMenuState::StartButtonOnClick()
    {
        _engine.RequestStateChange(std::make_unique<GameState>(_engine));
    }
    void MainMenuState::QuitButtonOnClick()
    {
        _engine.RequestQuit();
    }
    void MainMenuState::SettingsButtonOnClick()
    {
        _engine.RequestStateChange(std::make_unique<SettingsState>(_engine));
    }
    void MainMenuState::HandleEvent(const sf::Event& event)
    {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(_engine.GetWindow());
        sf::Vector2f worldPos = _engine.GetWindow().mapPixelToCoords(pixelPos);
        _gui.HandleEvent(event,worldPos);
    }
}
