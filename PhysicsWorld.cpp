#include "PhysicsWorld.h"
#include "Collision.h"
#include <algorithm>

void Noir2D::PhysicsWorld::AddDynamic(GameObject* obj)
{
	_dynamicObjects.push_back(obj);
}

void Noir2D::PhysicsWorld::AddStatic(GameObject* obj)
{
	_staticObjects.push_back(obj);
}

void Noir2D::PhysicsWorld::Step(float deltaTime)
{
	for (GameObject* dynamicObj : _dynamicObjects)
	{
		sf::Vector2f delta = dynamicObj->GetVelocity() * deltaTime;
		sf::FloatRect bounds = dynamicObj->GetBounds();
		//check x axis first
		sf::FloatRect nextX = bounds;
		nextX.left += delta.x;
		bool blockedX = std::any_of(_staticObjects.begin(), _staticObjects.end(),
			[&](GameObject* s) { return Collision::Intersects(nextX, s->GetBounds()); });
		//check y axis independtly
		sf::FloatRect nextY = bounds;
		nextY.top += delta.y;
		bool blockedY = std::any_of(_staticObjects.begin(), _staticObjects.end(),
			[&](GameObject* s) { return Collision::Intersects(nextY, s->GetBounds()); });

		dynamicObj->Move(sf::Vector2f(blockedX ? 0.f : delta.x, blockedY ? 0.f : delta.y));
	}
}
