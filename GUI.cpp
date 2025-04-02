#include "GUI.h"

void Noir2D::GUI::AddElement(std::shared_ptr<GUIElement> element) 
{
    _elements.push_back(element);
}

void Noir2D::GUI::HandleEvent(const sf::Event& event, const sf::Vector2f& mousePos) 
{
    if (!_enabled) return;
    for (auto& element : _elements) {
        if (element->IsEnabled()) {
            element->HandleEvent(event,mousePos);
        }
    }
}

void Noir2D::GUI::Draw(sf::RenderWindow& window) 
{
    if (!_visible) return;
    for (auto& element : _elements) 
    {
        if (element->IsVisible()) {
            element->Draw(window);
        }
    }
}

void Noir2D::GUI::Update(float deltaTime)
{
    for (auto& element : _elements) 
    {
            element->Update(deltaTime);
    }
}

void Noir2D::GUI::SetVisible(bool visible) 
{
    _visible = visible;
}

void Noir2D::GUI::SetEnabled(bool enabled) 
{
    _enabled = enabled;
}