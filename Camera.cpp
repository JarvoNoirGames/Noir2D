#include "Camera.h"
#include <algorithm>

namespace Noir2D
{
	Camera::Camera(const sf::Vector2f& viewSize)
	{
		_view.setSize(viewSize);
		_view.setCenter(viewSize.x / 2.f, viewSize.y / 2.f);
	}

	void Camera::SetWorldBounds(float width, float height)
	{
		_worldWidth = width;
		_worldHeight = height;
	}

	void Camera::SetTarget(GameObject* target)
	{
		_target = target;
	}

	void Camera::Update(float deltaTime)
	{
		if (!_target)
			return;

		sf::Vector2f targetPos = _target->GetPosition();
		sf::Vector2f viewSize = _view.getSize();

		float halfWidth = viewSize.x / 2.f;
		float halfHeight = viewSize.y / 2.f;

		float clampedX = targetPos.x;
		float clampedY = targetPos.y;

		if (_worldWidth > viewSize.x)
			clampedX = std::clamp(targetPos.x, halfWidth, _worldWidth - halfWidth);
		else
			clampedX = _worldWidth / 2.f; // world narrower than view — just center it

		if (_worldHeight > viewSize.y)
			clampedY = std::clamp(targetPos.y, halfHeight, _worldHeight - halfHeight);
		else
			clampedY = _worldHeight / 2.f;

		_view.setCenter(clampedX, clampedY);
	}

	const sf::View& Camera::GetView() const
	{
		return _view;
	}
}