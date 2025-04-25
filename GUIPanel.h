#pragma once
#include <vector>
#include <memory>
#include "GUIElement.h"

namespace Noir2D
{
	class GUIPanel : public GUIElement
	{
	public:
		enum class LayoutDirection { Vertical, Horizontal };

		GUIPanel(const sf::Vector2f& position, const sf::Vector2f& size,
			const sf::Color& backgroundColor = sf::Color(50, 50, 50, 200),
			LayoutDirection direction = LayoutDirection::Vertical,
			float padding = 10.f);

		void AddElement(std::shared_ptr<GUIElement> element);
		void Draw(sf::RenderWindow& window) override;
		void HandleEvent(const sf::Event& event, const sf::Vector2f& mousePos) override;
		void Update(float deltaTime) override;
		void UpdateLayout() override;
		void SetSize(const sf::Vector2f& size);

	private:
		sf::RectangleShape _background;
		std::vector<std::shared_ptr<GUIElement>> _elements;
		LayoutDirection _layoutDirection;
		float _padding;
	};
}