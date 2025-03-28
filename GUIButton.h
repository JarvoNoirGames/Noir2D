#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "GUIElement.h"

namespace Noir2D
{
	class GUIButton : public GUIElement
	{
	public:
		GUIButton(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font,
			const std::string& text, std::function<void()> onClick);
		void HandleEvent(const sf::Event& event) override;
		void Draw(sf::RenderWindow& window) override;
		void ChangeEnabledColour(bool enabled);
		sf::RectangleShape GetShape() { return _shape; }
	private:
		sf::RectangleShape _shape;
		sf::Text _label;
		std::function<void()> _onClick;
		bool _enabled = true;
		bool _isClicked = false;
	};
}