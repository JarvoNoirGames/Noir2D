#pragma once
#include <SFML/Graphics.hpp>
namespace Noir2D
{
	class State
	{
	public:
		virtual ~State() = default;
		virtual void Init() = 0;
		virtual void HandleEvent(const sf::Event& event) = 0;
		virtual void HandleInput() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Render(float deltaTime) = 0;
		virtual void Cleanup() = 0;
		virtual void Pause() {}
		virtual void Resume() {}
	};
}