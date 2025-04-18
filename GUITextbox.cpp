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
	_fullText = WrapTextToFit(text, _box.getSize().x - _padding.x * 2.f); // subtract padding
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
		if (charsToShow > _displayedText.size() && charsToShow <= _fullText.size()) //while still characters to display
		{
			_displayedText = _fullText.substr(0, charsToShow);
			_text.setString(_displayedText);
			UpdateLayout();
		}

		if (charsToShow >= _fullText.size())
		{
			_displayedText = _fullText; // Make sure the last character is included
			_text.setString(_displayedText);
			UpdateLayout();
			_isTyping = false;
		}
	}
}

void Noir2D::GUITextbox::Draw(sf::RenderWindow& window)
{
	window.draw(_box);
	window.draw(_text);
}

void Noir2D::GUITextbox::UpdateLayout()
{
	// Max width available for text, considering padding
	float maxWidth = _box.getSize().x - _padding.x * 2; // Available width considering padding
	float xPos = _box.getPosition().x + _padding.x;
	float yPos = _box.getPosition().y + _padding.y;
	float lineHeight = _text.getCharacterSize() * 1.2f; // Space between lines

	// Temporary string for current line and vector for storing wrapped lines
	std::string currentLine;
	std::vector<std::string> wrappedLines;

	// Split the text into words using a custom function to handle spaces
	std::vector<std::string> words = SplitTextIntoWords(_displayedText);

	for (const std::string& word : words) {
		// Temporarily append the word and check the width
		std::string potentialLine = currentLine + word + " "; // Add space after each word
		_text.setString(potentialLine); // Set the string to the text object

		// Check if the current line exceeds the available width
		if (_text.getLocalBounds().width > maxWidth) {
			// The word doesn’t fit, so we push the current line and start a new one
			if (!currentLine.empty()) {
				wrappedLines.push_back(currentLine); // Add the current line to the wrapped lines
			}
			currentLine = word + " "; // Start a new line with the current word
		}
		else {
			currentLine = potentialLine; // Add the word to the current line if it fits
		}
	}

	// If there’s any remaining text in currentLine, push it as the last line
	if (!currentLine.empty()) {
		wrappedLines.push_back(currentLine);
	}

	// Create the final wrapped text with new lines and set it to _text
	std::string wrappedText = "";
	for (const auto& line : wrappedLines) {
		wrappedText += line + "\n";  // Add newline after each wrapped line
	}

	_text.setString(wrappedText);  // Update the text object with all lines
	_text.setPosition(xPos, yPos); // Position the text within the box
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
			std::cout << "DEFAULT BREAK";
			break;
		}
	}
}

float Noir2D::GUITextbox::GetFontSize()
{
	return _fontSize;
}

void Noir2D::GUITextbox::SetFontSize(const float size)
{
	_fontSize = size;
}

std::string Noir2D::GUITextbox::WrapTextToFit(const std::string& text, float maxWidth)
{
		std::string wrapped;
		std::string word;
		sf::Text tempText;
		tempText.setFont(_font);

		for (char c : text) {
			if (c == ' ' || c == '\n') {
				tempText.setString(wrapped + word);
				if (tempText.getLocalBounds().width > maxWidth) {
					wrapped += '\n';
				}
				else if (!wrapped.empty()) {
					wrapped += ' ';
				}
				wrapped += word;
				word.clear();

				if (c == '\n') {
					wrapped += '\n'; // preserve manual line breaks
				}
			}
			else {
				word += c;
			}
		}

		// Add any remaining word
		if (!word.empty()) {
			tempText.setString(wrapped + word);
			if (tempText.getLocalBounds().width > maxWidth) {
				wrapped += '\n';
			}
			else if (!wrapped.empty()) {
				wrapped += ' ';
			}
			wrapped += word;
		}

		return wrapped;
	}

std::vector<std::string> Noir2D::GUITextbox::SplitTextIntoWords(const std::string& text)
{
	std::vector<std::string> words;
	std::string currentWord;

	for (size_t i = 0; i < text.length(); ++i) {
		char currentChar = text[i];

		// If it's a space or a newline, we add the current word and reset
		if (currentChar == ' ' || currentChar == '\n') {
			if (!currentWord.empty()) {
				words.push_back(currentWord);
				currentWord.clear();
			}
		}
		else {
			currentWord += currentChar; // Otherwise, keep adding to the current word
		}
	}

	// If there’s a final word that didn’t get added
	if (!currentWord.empty()) {
		words.push_back(currentWord);
	}

	return words;
}