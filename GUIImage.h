#pragma once
#include "GUIElement.h"
#include "ResolutionManager.h"
#include <SFML/Graphics.hpp>

namespace Noir2D
{
    class GUIImage : public GUIElement {
    public:
        GUIImage(const sf::Vector2f& position, const sf::Texture& texture, bool smooth = true);

        void Draw(sf::RenderWindow& window) override;
        void HandleEvent(const sf::Event& event, const sf::Vector2f& mousePos) override {}
        void Update(float dt) override {}
        void UpdateLayout() override;
        void SetSize(const sf::Vector2f& size);
        void SetOpacity(float alpha);  // Set transparency
        void SetPosition(const sf::Vector2f& position);

    private:
        sf::Sprite _sprite;
        sf::Vector2f _originalSize;
    };
}