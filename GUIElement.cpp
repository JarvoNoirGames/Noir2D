#include "GUIElement.h"

Noir2D::GUIElement::GUIElement(const sf::Vector2f& position)
    : _position(position), _visible(true), _enabled(true) {}

void Noir2D::GUIElement::SetPosition(const sf::Vector2f& position)
{
	_position = position;
}

sf::Vector2f Noir2D::GUIElement::GetPosition() const
{
	return _position;
}

void Noir2D::GUIElement::SetVisible(bool visible)
{
	_visible = visible;
}

bool Noir2D::GUIElement::IsVisible() const
{
	return _visible;
}

void Noir2D::GUIElement::SetEnabled(bool enabled)
{
	_enabled = enabled;
}

bool Noir2D::GUIElement::IsEnabled() const
{
	return _enabled;
}