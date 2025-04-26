#pragma once
#include <vector>
#include <memory>
#include "GUIElement.h"

namespace Noir2D
{
    class GUI {
    public:
        void AddElement(std::shared_ptr<GUIElement> element);

        void HandleEvent(const sf::Event& event, const sf::Vector2f& mousePos);
        void Draw(sf::RenderWindow& window);
        void Update(float deltaTime);
        void UpdateLayout();
        void SetVisible(bool visible);
        void SetEnabled(bool enabled);

    private:
        std::vector<std::shared_ptr<GUIElement>> _elements;
        bool _visible = true;
        bool _enabled = true;
    };
}

