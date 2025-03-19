#include "MainMenuState.h"
#include "GameState.h"
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

        _playButton.setFont(_font);
        _playButton.setString("Play");
        _playButton.setCharacterSize(30);
        _playButton.setPosition(350, 250);

        _exitButton.setFont(_font);
        _exitButton.setString("Exit");
        _exitButton.setCharacterSize(30);
        _exitButton.setPosition(350, 350);
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
    }

    void MainMenuState::Cleanup() 
    {
        _font = sf::Font();
    }
}
