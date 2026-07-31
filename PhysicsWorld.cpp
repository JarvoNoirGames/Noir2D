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
		sf::Vector2f velocity = dynamicObj->GetVelocity();

		// Gravity — inert unless both PhysicsWorld::SetGravity and the object's GravityScale are non-zero
		velocity += _gravity * dynamicObj->GetGravityScale() * deltaTime;

		// Friction — inert unless the object sets a non-zero friction value.
		// Damps velocity toward zero rather than snapping it, so it reads as deceleration, not an abrupt stop.
		float friction = dynamicObj->GetFriction();
		if (friction > 0.f)
		{
			float dampFactor = std::max(0.f, 1.f - friction * deltaTime);
			velocity *= dampFactor;
		}

		dynamicObj->SetVelocity(velocity);

		sf::Vector2f delta = velocity * deltaTime;
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

void Noir2D::PhysicsWorld::SetGravity(const sf::Vector2f& gravity)
{
	_gravity = gravity;
}
