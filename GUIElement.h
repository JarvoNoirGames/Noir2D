#pragma once
#include <SFML/Graphics.hpp>

namespace Noir2D
{
	class GUIElement
	{
	public:
		GUIElement(const sf::Vector2f& position);
		virtual ~GUIElement() = default;

		virtual void Draw(sf::RenderWindow& window) = 0;
		virtual void HandleEvent(const sf::Event& event, const sf::Vector2f& mousePos) = 0;
		virtual void SetHovered(bool hovered) {}
		virtual void Update(float deltaTime) {}
		virtual void UpdateLayout() = 0;
		void SetPosition(const sf::Vector2f& position);
		sf::Vector2f GetPosition() const;
		void SetOriginalPosition(const sf::Vector2f& position);
		sf::Vector2f GetOriginalPosition() const;
		void SetOriginalSize(const sf::Vector2f& size);
		sf::Vector2f GetOriginalSize() const;
		void SetVisible(bool visible);
		bool IsVisible() const;
		void SetEnabled(bool enabled);
		bool IsEnabled() const;
	private:
		sf::Vector2f _position;
		sf::Vector2f _originalPosition;
		sf::Vector2f _originalSize;
		bool _visible;
		bool _enabled;
	};
}
