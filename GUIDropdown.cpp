#include "GUIDropdown.h"

Noir2D::GUIDropdown::GUIDropdown(const sf::Vector2f& position, sf::Font& font, const std::vector<std::string>& options) : GUIElement(position),_isOpen(false)
{
    _mainBox.setSize({ 200, 40 });
    _mainBox.setPosition(position);
    _mainBox.setFillColor(sf::Color::Blue);

    _selectedText.setFont(font);
    _selectedText.setCharacterSize(24);
    _selectedText.setFillColor(sf::Color::White);
    _selectedText.setPosition(position.x + 10, position.y + 5);
    _selectedText.setString(options.empty() ? "" : options[0]);

    for (size_t i = 0; i < options.size(); ++i) {
        sf::RectangleShape box({ 200, 40 });
        box.setPosition(position.x, position.y + (i + 1) * 40);
        box.setFillColor(sf::Color::White);

        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Black);
        text.setString(options[i]);
        text.setPosition(position.x + 10, position.y + (i + 1) * 40 + 5);

        _optionBoxes.push_back(box);
        _optionTexts.push_back(text);
    }
}

void Noir2D::GUIDropdown::Draw(sf::RenderWindow& window)
{
    if (!IsVisible()) return;
    window.draw(_mainBox);
    window.draw(_selectedText);

    if (_isOpen) {
        for (size_t i = 0; i < _optionBoxes.size(); ++i) {
            window.draw(_optionBoxes[i]);
            window.draw(_optionTexts[i]);
        }
    }
}

void Noir2D::GUIDropdown::HandleEvent(const sf::Event& event)
{
    if (!IsEnabled()) return;

    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        if (_mainBox.getGlobalBounds().contains(mousePos)) {
            Toggle();
        }
        else if (_isOpen) {
            for (size_t i = 0; i < _optionBoxes.size(); ++i) {
                if (_optionBoxes[i].getGlobalBounds().contains(mousePos)) {
                    _selectedText.setString(_optionTexts[i].getString());
                    Toggle();
                    if (_onSelect) {
                        _onSelect(_optionTexts[i].getString());
                    }
                    break;
                }
            }
        }
    }
}

std::string Noir2D::GUIDropdown::GetSelectedOption() const
{
    return _selectedText.getString();
}

void Noir2D::GUIDropdown::SetCallback(std::function<void(const std::string&)> callback)
{
    _onSelect = callback;
}

void Noir2D::GUIDropdown::Toggle()
{
    _isOpen = !_isOpen;
}
