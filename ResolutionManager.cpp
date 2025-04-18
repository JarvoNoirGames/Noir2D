#include "ResolutionManager.h"

Noir2D::ResolutionManager& Noir2D::ResolutionManager::GetInstance()
{
	static ResolutionManager instance;
	return instance;
}

void Noir2D::ResolutionManager::SetBaseResolution(const sf::Vector2u& base)
{
	_baseResolution = base;
}

void Noir2D::ResolutionManager::SetWindowSize(const sf::Vector2u& current)
{
	_currentWindowSize = current;
}

float Noir2D::ResolutionManager::GetScaleX() const
{
	return static_cast<float>(_currentWindowSize.x) / _baseResolution.x;
}

float Noir2D::ResolutionManager::GetScaleY() const
{
	return static_cast<float>(_currentWindowSize.y) / _baseResolution.y;
}

const sf::Vector2u& Noir2D::ResolutionManager::GetBaseResolution() const
{
	return _baseResolution;
}

const sf::Vector2u& Noir2D::ResolutionManager::GetCurrentWindowSize() const
{
	return _currentWindowSize;
}
