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

		//debug grid
		_debugGrid = std::make_unique<DebugGrid>(2000, 2000, 100);

		//test gameobject
		_rogueTexture = &AssetManager::GetInstance().GetTexture("anim_test");
		_rogue = std::make_unique<GameObject>(*_rogueTexture);
		auto anim = std::make_unique<Animation>(sf::Vector2i(32, 32), 10, 0.12f);
		anim->SetRow(0);
		anim->Play();
		_rogue->SetAnimation(std::move(anim));
		_rogue->SetPosition({ 200.f, 200.f });

		//camera
		sf::Vector2u windowSize = _engine.GetWindow().getSize();
		_camera = std::make_unique<Camera>(sf::Vector2f((float)windowSize.x, (float)windowSize.y));
		_camera->SetWorldBounds(2000.f, 2000.f);
		_camera->SetTarget(_rogue.get());

		//physics test
		_wall = std::make_unique<GameObject>(*_rogueTexture);
		_wall->SetStatic(true);
		_wall->SetPosition({ 200.f, 400.f });

		_physicsWorld = std::make_unique<PhysicsWorld>();
		_physicsWorld->AddDynamic(_rogue.get());
		_physicsWorld->AddStatic(_wall.get());
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
		if (_rogue)
		{
			//test input for now - move to PlayerController later when implemented
			float speed = 150.f; // pixels per second
			sf::Vector2f velocity(0.f,0.f);

			if (InputManager::GetInstance().IsKeyPressed(sf::Keyboard::W)) velocity.y -= speed;
			if (InputManager::GetInstance().IsKeyPressed(sf::Keyboard::S)) velocity.y += speed;
			if (InputManager::GetInstance().IsKeyPressed(sf::Keyboard::A)) velocity.x -= speed;
			if (InputManager::GetInstance().IsKeyPressed(sf::Keyboard::D)) velocity.x += speed;

			_rogue->SetVelocity(velocity);

			_rogue->Update(deltaTime);
		}

		if (_physicsWorld)
			_physicsWorld->Step(deltaTime);

		if (_camera)
			_camera->Update(deltaTime);
	}

	void GameState::Render(float deltaTime)
	{
		sf::RenderWindow& window = _engine.GetWindow();

		if (_camera)
			window.setView(_camera->GetView());   // world-space view starts here

		if (_debugGrid)
			_debugGrid->Draw(window);
		if (_rogue)
			_rogue->Draw(window);
		if (_wall)
			_wall->Draw(window);

		window.setView(window.getDefaultView()); // back to screen-space for UI
		window.draw(_title);
		_gui.Draw(window);
	}

	void GameState::Cleanup()
	{
		_font = sf::Font();
		if (_camera)
			_camera->SetTarget(nullptr);   // clear the watcher before the watched object goes away
		_camera.reset();
		_rogue.reset();
		_rogueTexture = nullptr;
		_debugGrid.reset();
		_physicsWorld.reset();
		_wall.reset();
	}
	void GameState::ReturnToMainMenu()
	{
		if (!_engine.GetStateMachine().IsEmpty()) {  // Ensure there's a state to return to
			_engine.RequestStateChange(std::make_unique<MainMenuState>(_engine));
		}
	}
}