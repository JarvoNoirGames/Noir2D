#include "GameState.h"
#include "PauseState.h"
#include "SettingsState.h"
#include "MainMenuState.h"
#include "GUITextbox.h"

namespace Noir2D
{
	GameState::GameState(Engine& engine) : _engine(engine) {}

	void GameState::Init()
	{
		_font = AssetManager::GetInstance().GetFont("default");

		/*auto backButton = std::make_shared<GUIButton>(
			sf::Vector2f(600, 500), sf::Vector2f(100, 50), _font, "Back",
			[this]() {sf::Vector2f(400, 300), ReturnToMainMenu(); }
		);
		_gui.AddElement(backButton);*/
		const sf::Texture& logoTexture = AssetManager::GetInstance().GetTexture("splash_logo");
		auto imageButton = std::make_shared<GUIImageButton>(sf::Vector2f(600, 500), sf::Vector2f(100, 50), logoTexture, [this]() {ReturnToMainMenu(); });
		_gui.AddElement(imageButton);

		// Example text content
		std::string dialogue = "Welcome to the game! Look at my GUITextbox with a typing effect that handles word wrapping as well, I had to take 2 ibuprofen after getting this to work!";
		auto textbox = std::make_shared<GUITextbox>
			(sf::Vector2f(100, 100), // Position
				sf::Vector2f(600, 100), // Size
				_font,
				dialogue,
				24.f // Font size
			);
		_gui.AddElement(textbox);
	}

	void GameState::HandleEvent(const sf::Event& event)
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(_engine.GetWindow());
		sf::Vector2f worldPos = _engine.GetWindow().mapPixelToCoords(pixelPos);
		_gui.HandleEvent(event, worldPos);
	}

	void GameState::HandleInput() {
		InputManager& input = InputManager::GetInstance();
		if (input.IsKeyPressed(sf::Keyboard::Escape))
		{
			_engine.GetStateMachine().PushState(std::make_unique<PauseState>(_engine));
		}
	}

	void GameState::Update(float deltaTime)
	{
		_gui.Update(deltaTime);
	}

	void GameState::Render(float deltaTime)
	{
		sf::RenderWindow& window = _engine.GetWindow();
		window.draw(_title);
		_gui.Draw(window);
	}

	void GameState::Cleanup()
	{
		_font = sf::Font();
	}
	void GameState::ReturnToMainMenu()
	{
		if (!_engine.GetStateMachine().IsEmpty()) {  // Ensure there's a state to return to
			_engine.RequestStateChange(std::make_unique<MainMenuState>(_engine));
		}
	}
}