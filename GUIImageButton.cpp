#include "GUIImageButton.h"

Noir2D::GUIImageButton::GUIImageButton(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Texture& texture, std::function<void()> onClick) : GUIElement(position), _onClick(std::move(onClick))
{
	const float padding = 5.0f;

	_shape.setPosition(position);
	_shape.setSize(size);
	_shape.setFillColor(sf::Color::Transparent);
	_shape.setOutlineThickness(3.f);
	_shape.setOutlineColor(sf::Color::White);

	// Adjust sprite size for padding
	sf::Vector2f paddedSize = { size.x - 2 * padding, size.y - 2 * padding };
	_sprite.setTexture(texture);
	_sprite.setPosition(position.x + padding, position.y + padding);

	const sf::Vector2f textureSize(texture.getSize());

	_sprite.setScale(
		paddedSize.x / textureSize.x,
		paddedSize.y / textureSize.y
	);
}

void Noir2D::GUIImageButton::Draw(sf::RenderWindow& window)
{
	if (IsVisible())
	{
		window.draw(_shape);
		window.draw(_sprite);
	}
}

void Noir2D::GUIImageButton::HandleEvent(const sf::Event& event, const sf::Vector2f& mousePos)
{
	if (!IsEnabled() || !IsVisible())
		return;

	const bool contains = _sprite.getGlobalBounds().contains(mousePos);

	switch (event.type)
	{
	case sf::Event::MouseMoved:
		SetHovered(contains);
		break;
	case sf::Event::MouseButtonPressed:
		if (event.mouseButton.button == sf::Mouse::Left && contains)
			_isClicked = true;
		break;
	case sf::Event::MouseButtonReleased:
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (_isClicked && contains && _onClick)
				_onClick();
			_isClicked = false;
		}
		break;
	default:
		break;
	}
}

void Noir2D::GUIImageButton::UpdateLayout()
{
	const sf::Vector2f size = _shape.getSize();
	const sf::Vector2f textureSize(_sprite.getTexture()->getSize());
	_sprite.setScale(
		size.x / textureSize.x,
		size.y / textureSize.y
	);
	_sprite.setPosition(GetPosition());
	_shape.setPosition(GetPosition());
}

void Noir2D::GUIImageButton::SetHovered(bool hovered)
{
	_hovered = hovered;
	_sprite.setColor(_hovered ? _spriteHoverColour : _spriteNormalColour);
}

void Noir2D::GUIImageButton::SetScale(float x, float y)
{
	_shape.setScale(sf::Vector2f(x, y));
	_sprite.setScale(sf::Vector2f(x, y));
}

void Noir2D::GUIImageButton::SetSize(const sf::Vector2f& size)
{
	_size = size;
	UpdateLayout();
}

sf::Vector2f Noir2D::GUIImageButton::GetSize() const
{
	return _size;
}
