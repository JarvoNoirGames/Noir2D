#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

namespace Noir2D
{
	class Camera
	{
	public:
		Camera(const sf::Vector2f& viewSize);

		void SetWorldBounds(float width, float height);
		void SetTarget(GameObject* target);

		void Update(float deltaTime);
		const sf::View& GetView() const;

	private:
		sf::View _view;
		GameObject* _target = nullptr;

		float _worldWidth = 0.f;
		float _worldHeight = 0.f;
	};
}