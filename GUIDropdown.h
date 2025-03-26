#pragma once
#include "GUIElement.h"
#include <vector>
#include <functional>

namespace Noir2D
{
    class GUIDropdown : public GUIElement {
    public:
        GUIDropdown(const sf::Vector2f& position, sf::Font& font, const std::vector<std::string>& options);

        void Draw(sf::RenderWindow& window) override;
        void HandleEvent(const sf::Event& event) override;

        std::string GetSelectedOption() const;
        void SetCallback(std::function<void(const std::string&)> callback);

    private:
        sf::RectangleShape _mainBox;
        sf::Text _selectedText;

        std::vector<sf::Text> _optionTexts;
        std::vector<sf::RectangleShape> _optionBoxes;

        bool _isOpen = false;
        std::function<void(const std::string&)> _onSelect;

        void Toggle();
    };
}

