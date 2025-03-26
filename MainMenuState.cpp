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

        auto startButton = std::make_shared<GUIButton>(
            sf::Vector2f(400, 200), sf::Vector2f(200, 50),_font, "Start Game",
            [this]() {sf::Vector2f(400, 200), _engine.RequestStateChange(std::make_unique<GameState>(_engine)); } // Use make_unique
        );

        auto quitButton = std::make_shared<GUIButton>(
            sf::Vector2f(400, 300), sf::Vector2f(200, 50), _font, "Quit",
            [this]() {sf::Vector2f(400, 300), _engine.RequestQuit(); }
        );

        // Dropdown options for screen resolutions
        std::vector<std::string> resolutions = { "800x600", "1280x720", "1920x1080", "2560x1440" };

        // Create the dropdown and position it at the center of the screen
        _dropdown = std::make_shared<GUIDropdown>(
            sf::Vector2f(400, 300), _font, resolutions
        );
        
        // Set callback for when a resolution is selected
        _dropdown->SetCallback([](const std::string& selectedOption) {
            std::cout << "Resolution changed to: " << selectedOption << std::endl;
            });
        // Add the dropdown to the GUI container
        //_gui.AddElement(_dropdown);
        _gui.AddElement(startButton);
        _gui.AddElement(quitButton);
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
    void MainMenuState::HandleEvent(const sf::Event& event)
    {
        _gui.HandleEvent(event);
    }
}
