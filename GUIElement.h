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
		virtual void HandleEvent(const sf::Event& event) = 0;

		void SetPosition(const sf::Vector2f& position);
		sf::Vector2f GetPosition() const;

		void SetVisible(bool visible);
		bool IsVisible() const;

		void SetEnabled(bool enabled);
		bool IsEnabled() const;
	private:
		sf::Vector2f _position;
		bool _visible;
		bool _enabled;
	};
}
