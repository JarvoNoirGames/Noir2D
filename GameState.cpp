#include "GameState.h"
#include "PauseState.h"
#include "SettingsState.h"
#include "MainMenuState.h"
#include "GUITextbox.h"
#include "GUIPanel.h"
#include <iostream>

namespace Noir2D
{
	GameState::GameState(Engine& engine) : _engine(engine) {}

	void GameState::Init()
	{
		_font = AssetManager::GetInstance().GetFont("default");

		// Create a panel that holds buttons
		auto buttonPanel = std::make_shared<GUIPanel>(
			sf::Vector2f(200,200),   //position
			sf::Vector2f(150, 200),   //size
			sf::Color(50, 50, 50, 150),
			GUIPanel::LayoutDirection::Vertical,
			15.f                      //padding
		);

		// Create buttons to go in the panel
		std::vector<std::pair<std::string, std::function<void()>>> buttonData = {
			{ "Back 1", [this]() { ReturnToMainMenu(); } },
			{ "Back 2", [this]() { ReturnToMainMenu(); } },
			{ "Back 3", [this]() { ReturnToMainMenu(); } }
		};

		for (const auto& [label, callback] : buttonData)
		{
			auto btn = std::make_shared<GUIButton>(
				sf::Vector2f(0, 0),
				sf::Vector2f(100, 50),
				_font, label, callback
			);
			buttonPanel->AddElement(btn);
		}
		//test anim
		_rogueTexture = &AssetManager::GetInstance().GetTexture("anim_test");
		sf::Vector2i frameSize(32, 32);
		_rogueAnim = std::make_unique<Animation>(*_rogueTexture, frameSize, 10, 0.12f);
		_rogueAnim->SetRow(0);
		_rogueAnim->SetPosition({ 200.f, 200.f });
		_rogueAnim->Play();
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
		if (_rogueAnim)
			_rogueAnim->Update(deltaTime);
	}

	void GameState::Render(float deltaTime)
	{
		sf::RenderWindow& window = _engine.GetWindow();
		window.draw(_title);
		_gui.Draw(window);
		if (_rogueAnim)
			_rogueAnim->Draw(window);
	}

	void GameState::Cleanup()
	{
		_font = sf::Font();
		_rogueAnim.reset();
		_rogueTexture = nullptr;
	}
	void GameState::ReturnToMainMenu()
	{
		if (!_engine.GetStateMachine().IsEmpty()) {  // Ensure there's a state to return to
			_engine.RequestStateChange(std::make_unique<MainMenuState>(_engine));
		}
	}
}