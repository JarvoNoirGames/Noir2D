#include "GameState.h"
#include "Engine.h"

namespace Noir2D
{
	GameState::GameState(Engine& engine)
		: _engine(engine)
	{
	}

	void GameState::Init()
	{
		sf::Vector2u windowSize = _engine.GetWindow().getSize();

		_camera = std::make_unique<Camera>(sf::Vector2f((float)windowSize.x, (float)windowSize.y));
		_physicsWorld = std::make_unique<PhysicsWorld>();

		// Platform/player GameObjects, camera bounds/target, and physics registration
		// get set up here once the level layout exists
	}

	void GameState::HandleEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
			sf::Vector2f worldPos = _engine.GetWindow().mapPixelToCoords(mousePos, _engine.GetWindow().getDefaultView());
			_gui.HandleEvent(event, worldPos);
		}
	}

	void GameState::HandleInput()
	{
		// Continuous/held-input checks (movement, held actions) go here
	}

	void GameState::Update(float deltaTime)
	{
		_gui.Update(deltaTime);

		// Dynamic GameObject updates go here

		if (_physicsWorld)
			_physicsWorld->Step(deltaTime);

		if (_camera)
			_camera->Update(deltaTime);
	}

	void GameState::Render(float deltaTime)
	{
		sf::RenderWindow& window = _engine.GetWindow();

		if (_camera)
			window.setView(_camera->GetView());

		// World-space drawing (platforms, player) goes here

		window.setView(window.getDefaultView());
		_gui.Draw(window);
	}

	void GameState::Cleanup()
	{
		if (_camera)
			_camera->SetTarget(nullptr);

		_camera.reset();
		_physicsWorld.reset();
	}
}