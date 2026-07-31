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

	private:
		std::vector<GameObject*> _dynamicObjects; // non-owning
		std::vector<GameObject*> _staticObjects;  // non-owning
	};
}