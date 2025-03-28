#include "MainMenuState.h"
#include "GameState.h"
#include "SettingsState.h"
#include <iostream>
namespace Noir2D
{
    MainMenuState::MainMenuState(Engine& engine) : _engine(engine) {}

	void MainMenuState::Init()
	{
		_font = AssetManager::GetInstance().GetFont("default");

		_title.setFont(_font);
        _title.setString("Main Menu");
        _title.setCharacterSize(50);
        _title.setPosition(300, 100);

        auto startButton = std::make_shared<GUIButton>(
            sf::Vector2f(400, 200), sf::Vector2f(200, 50),_font, "Start Game",
            [this]() {sf::Vector2f(400, 200), StartButtonOnClick(); }
        );

        auto quitButton = std::make_shared<GUIButton>(
            sf::Vector2f(400, 300), sf::Vector2f(200, 50), _font, "Quit",
            [this]() {sf::Vector2f(400, 300), QuitButtonOnClick(); }
        );

        auto settingsButton = std::make_shared<GUIButton>(
            sf::Vector2f(400, 400), sf::Vector2f(200, 50), _font, "Settings",
            [this]() {sf::Vector2f(400, 400), SettingsButtonOnClick(); }
        );

        _gui.AddElement(startButton);
        _gui.AddElement(quitButton);
        _gui.AddElement(settingsButton);
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

    }

    void MainMenuState::Render(float deltaTime)
    {
        sf::RenderWindow& window = _engine.GetWindow();
        window.draw(_title);
        window.draw(_playButton);
        window.draw(_exitButton);
        _gui.Draw(window);
    }

    void MainMenuState::Cleanup() 
    {
        _font = sf::Font();
        //these will be replaced by GUI buttons soon
        _playButton = sf::Text();
        _exitButton = sf::Text();
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
        _gui.HandleEvent(event);
    }
}
