#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "GUIElement.h"
#include "ResolutionManager.h"

namespace Noir2D
{
	class GUIImageButton : public GUIElement
	{
	public:
		GUIImageButton(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Texture& texture, std::function<void()> onClick);
		void Draw(sf::RenderWindow& window) override;
		void HandleEvent(const sf::Event& event, const sf::Vector2f& mousePos) override;
		void UpdateLayout() override;
		void SetHovered(bool hovered) override;
		void SetScale(float x, float y);
		void SetSize(const sf::Vector2f& size);
		sf::Vector2f GetSize() const;
		sf::RectangleShape GetShape() { return _shape; };
	private:
		sf::RectangleShape _shape;
		sf::Sprite _sprite;
		std::function<void()> _onClick;
		bool _hovered = false;
		bool _isClicked = false;
		sf::Vector2f _size;
		sf::Color _normalColour = sf::Color::Transparent;
		sf::Color _hoverColour = sf::Color::White;
		sf::Color _spriteNormalColour = sf::Color(255,255,255,255);
		sf::Color _spriteHoverColour = sf::Color(255, 255, 255, 150);
	};
}