#include "GUIImage.h"
#include <iostream>
#include "GUITextbox.h"

Noir2D::GUITextbox::GUITextbox(const sf::Vector2f& position, const sf::Vector2f& size, sf::Font& font, const std::string& text, unsigned int fontSize, const sf::Color& textColor, const sf::Color& backgroundColor, const sf::Color& outlineColor, float outlineThickness) : GUIElement(position), _font(font)
{
	_box.setSize(size);
	_box.setPosition(position);
	_box.setFillColor(backgroundColor);
	_box.setOutlineColor(outlineColor);
	_box.setOutlineThickness(outlineThickness);

	_text.setFont(_font);
	_text.setCharacterSize(fontSize);
	_text.setFillColor(textColor);
	_text.setString("");

	SetText(text);
}

void Noir2D::GUITextbox::SetText(const std::string& text)
{
	_fullText = text;
	_displayedText.clear();
	_text.setString("");
	_typingTimer = 0.0f;
	_isTyping = _typingEnabled;
	if (!_typingEnabled)
	{
		_text.setString(_fullText);
		_isTyping = false;
	}

	UpdateLayout();
}

void Noir2D::GUITextbox::SetTypingEnabled(bool enabled)
{
	_typingEnabled = enabled;
}

void Noir2D::GUITextbox::SetTypingSpeed(float charactersPerSecond)
{
	_typingSpeed = charactersPerSecond;
}

void Noir2D::GUITextbox::SkipTyping()
{
	_isTyping = false;
	_text.setString(_fullText);
	UpdateLayout();
}

bool Noir2D::GUITextbox::IsTyping() const
{
	return _isTyping;
}

void Noir2D::GUITextbox::Update(float deltaTime)
{
	if (_isTyping)
	{
		_typingTimer += deltaTime;
		size_t charsToShow = static_cast<size_t>(_typingTimer * _typingSpeed);
		if (charsToShow > _displayedText.size() && charsToShow < _fullText.size()) //while still characaters to display
		{
			_displayedText = _fullText.substr(0, charsToShow);
			_text.setString(_displayedText);
			UpdateLayout();
		}

		if (charsToShow >= _fullText.size())
			_isTyping = false;
	}
}

void Noir2D::GUITextbox::Draw(sf::RenderWindow& window)
{
	window.draw(_box);
	window.draw(_text);
}

void Noir2D::GUITextbox::UpdateLayout()
{
	sf::FloatRect textBounds = _text.getLocalBounds();
	_text.setOrigin(textBounds.left, textBounds.top);
	_text.setPosition(_box.getPosition().x + 10.0f, _box.getPosition().y + 10.0f);
}

void Noir2D::GUITextbox::CompleteText()
{
	if (_isTyping)
	{
		_displayedText = _fullText;
		_text.setString(_displayedText);
		_isTyping = false;
		UpdateLayout();
	}
}

void Noir2D::GUITextbox::HandleEvent(const sf::Event& event, const sf::Vector2f& mousePos)
{
	if (_isTyping)
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Space)
				CompleteText();
			break;
		case sf::Event::MouseButtonPressed:
			CompleteText();
			break;
		default:
			break;
		}
	}
}
