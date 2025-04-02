#pragma once
#include <SFML/Graphics.hpp>
#include "GUIElement.h"

namespace Noir2D
{
	class GUILabel : public GUIElement
	{
	public:
		GUILabel() = default;
		GUILabel(const sf::Vector2f& position, const std::string& text, sf::Font& font, unsigned int fontSize = 20,
			const sf::Color& textColor = sf::Color::White, bool hasBackground = false);
		void HandleEvent(const sf::Event& event, const sf::Vector2f& mousePos) override;
		void Draw(sf::RenderWindow& window) override;
		void SetHovered(bool hovered) override;
		void Update(float deltaTime) override;
		void SetText(const std::string& newText);
		void SetColor(const sf::Color& textColor);
		void SetBackgroundColor(const sf::Color& bgColor);
		void SetOutline(float thickness, const sf::Color& outlineColor);
		void SetShadow(const sf::Vector2f& offset, const sf::Color& shadowColor);
		void SetBlinkEffect(bool enable, float speed = 1.0f);
		void SetAlignment(const std::string& align);
		void UpdateBackground();
	private:
		sf::Text _text;
		sf::Text _shadowText;
		sf::RectangleShape _background;
		bool _hasBackground;
		bool _blinkEffect = false;
		float _blinkSpeed = 1.0f;
		float _elapsedTime = 0.0f;
		std::string _alignment;
	};
}