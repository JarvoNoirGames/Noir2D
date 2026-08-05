#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "State.hpp"
#include "GUI.h"
#include "Camera.h"
#include "PhysicsWorld.h"

namespace Noir2D
{
	class Engine;

	class GameState : public State
	{
	public:
		GameState(Engine& engine);

		void Init() override;
		void HandleEvent(const sf::Event& event) override;
		void HandleInput() override;
		void Update(float deltaTime) override;
		void Render(float deltaTime) override;
		void Cleanup() override;

	private:
		Engine& _engine;

		GUI _gui;
		std::unique_ptr<Camera> _camera;
		std::unique_ptr<PhysicsWorld> _physicsWorld;

		// Platform/player GameObjects get added here as the platformer is built
	};
}