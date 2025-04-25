#include "GUIPanel.h"
#include <iostream>

Noir2D::GUIPanel::GUIPanel(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& backgroundColor, LayoutDirection direction, float padding) : GUIElement(position), _layoutDirection(direction), _padding(padding)
{
	_background.setPosition(position);
	_background.setSize(size);
	_background.setFillColor(backgroundColor);
	SetOriginalSize(size);
}

void Noir2D::GUIPanel::AddElement(std::shared_ptr<GUIElement> element)
{
	_elements.push_back(element);
	UpdateLayout();
}

void Noir2D::GUIPanel::Draw(sf::RenderWindow& window)
{
	if (!IsVisible())
		return;

	window.draw(_background);
	for (auto& element : _elements)
	{
		if (element->IsVisible())
			element->Draw(window);
	}
}

void Noir2D::GUIPanel::HandleEvent(const sf::Event& event, const sf::Vector2f& mousePos)
{
	if (!IsEnabled())
		return;

	for (auto& element : _elements)
		element->HandleEvent(event,mousePos);
}

void Noir2D::GUIPanel::Update(float deltaTime)
{
	for (auto& element : _elements)
		element->Update(deltaTime);
}

void Noir2D::GUIPanel::UpdateLayout()
{
	std::size_t elementCount = _elements.size();
	if (elementCount == 0)
		return;

	sf::Vector2f panelSize = _background.getSize();
	sf::Vector2f currentOffset = GetPosition() + sf::Vector2f(_padding, _padding);

	float totalPadding = _padding * (elementCount - 1);
	sf::Vector2f elementSize;

	switch (_layoutDirection)
	{
	case Noir2D::GUIPanel::LayoutDirection::Vertical:
		elementSize.x = panelSize.x - 2 * _padding;
		elementSize.y = (panelSize.y - 2 * _padding - totalPadding) / elementCount;
		break;
	case Noir2D::GUIPanel::LayoutDirection::Horizontal:
		elementSize.x = (panelSize.x - 2 * _padding - totalPadding) / elementCount;
		elementSize.y = panelSize.y - 2 * _padding;
		break;
	default:
		break;
	}

	// Clamp values here
	//elementSize.x = std::clamp(elementSize.x, 50.f, 300.f); // adjust as needed
	//elementSize.y = std::clamp(elementSize.y, 30.f, 100.f);

	for (auto& elem : _elements)
	{
		elem->SetPosition(currentOffset);
		elem->SetOriginalSize(elementSize);
		elem->UpdateLayout();

		switch (_layoutDirection)
		{
		case Noir2D::GUIPanel::LayoutDirection::Vertical:
			currentOffset.y += elementSize.y + _padding;
			break;
		case Noir2D::GUIPanel::LayoutDirection::Horizontal:
			currentOffset.x += elementSize.x + _padding;
			break;
		default:
			break;
		}
	}
}

void Noir2D::GUIPanel::SetSize(const sf::Vector2f& size)
{
	_background.setSize(size);
	SetOriginalSize(size);
	UpdateLayout();
}
