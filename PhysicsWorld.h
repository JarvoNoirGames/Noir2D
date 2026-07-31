#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameObject.h"

namespace Noir2D
{
	class PhysicsWorld
	{
	public:
		void AddDynamic(GameObject* obj);
		void AddStatic(GameObject* obj);
		void Step(float deltaTime);
		void SetGravity(const sf::Vector2f& gravity);

	private:
		std::vector<GameObject*> _dynamicObjects; // non-owning
		std::vector<GameObject*> _staticObjects;  // non-owning
		sf::Vector2f _gravity{ 0.f, 0.f }; // (0,0) = no gravity, default off
	};
}