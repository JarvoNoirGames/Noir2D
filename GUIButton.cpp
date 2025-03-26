#include "GUIButton.h"

	Noir2D::GUIButton::GUIButton(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font, const std::string& text, std::function<void()> onClick):GUIElement(position), _onClick(std::move(onClick))
	{
        _shape.setPosition(position);
        _shape.setSize(size);
        _shape.setFillColor(sf::Color(100, 100, 250)); // Default color

        _label.setFont(font);
        _label.setString(text);
        _label.setCharacterSize(20);
        _label.setFillColor(sf::Color::White);

        // Center text inside the button
        sf::FloatRect textBounds = _label.getLocalBounds();
        _label.setOrigin(textBounds.left + textBounds.width / 2.0f,
            textBounds.top + textBounds.height / 2.0f);
        _label.setPosition(position.x + size.x / 2.0f, position.y + size.y / 2.0f);
	}

	void Noir2D::GUIButton::HandleEvent(const sf::Event& event)
	{
        if (!_enabled) return;
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            if (_shape.getGlobalBounds().contains(mousePos)) {
                if (_onClick)
                    _onClick();
            }
        }
	}

	void Noir2D::GUIButton::Draw(sf::RenderWindow& window)
	{
        if (_enabled) 
        {
            window.draw(_shape);
            window.draw(_label);
        }
	}

    void Noir2D::GUIButton::ChangeEnabledColour(bool enabled)
    {
        _shape.setFillColor(enabled ? sf::Color(100, 100, 250) : sf::Color(50, 50, 50)); // Dim when disabled

    }
