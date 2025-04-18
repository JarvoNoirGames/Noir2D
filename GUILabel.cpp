#include "GUILabel.h"


Noir2D::GUILabel::GUILabel(const sf::Vector2f& position, const std::string& text, sf::Font& font, unsigned int fontSize, const sf::Color& textColor, bool hasBackground) :GUIElement(position), _hasBackground(hasBackground),_alignment("centre")
{
	// Setup text
	_text.setFont(font);
	_text.setString(text);
	_text.setCharacterSize(fontSize);
	_text.setFillColor(textColor);
	_text.setPosition(position);

	// Properly calculate background size if enabled
	if (_hasBackground) {
		UpdateBackground();
	}

	// Initialize shadow text (hidden by default)
	_shadowText = _text;
	_shadowText.setFillColor(sf::Color(0, 0, 0, 100)); // Semi-transparent black shadow
}

void Noir2D::GUILabel::HandleEvent(const sf::Event& event, const sf::Vector2f& mousePos)
{
}

void Noir2D::GUILabel::SetText(const std::string& newText) {
	_text.setString(newText);
	UpdateBackground();
}

void Noir2D::GUILabel::SetColor(const sf::Color& textColor) {
	_text.setFillColor(textColor);
}

void Noir2D::GUILabel::SetBackgroundColor(const sf::Color& bgColor) {
	if (_hasBackground) {
		_background.setFillColor(bgColor);
	}
}

void Noir2D::GUILabel::SetOutline(float thickness, const sf::Color& outlineColor)
{
	_text.setOutlineThickness(thickness);
	_text.setOutlineColor(outlineColor);
}

void Noir2D::GUILabel::SetShadow(const sf::Vector2f& offset, const sf::Color& shadowColor)
{
	_shadowText.setPosition(_text.getPosition() + offset);
	_shadowText.setFillColor(shadowColor);
}

void Noir2D::GUILabel::SetBlinkEffect(bool enable, float speed)
{
	_blinkEffect = enable;
	_blinkSpeed = speed;
}

void Noir2D::GUILabel::SetAlignment(const std::string& align) {
	_alignment = align;
	sf::FloatRect textBounds = _text.getLocalBounds();

	if (_alignment == "center") {
		_text.setOrigin(textBounds.width / 2, textBounds.height / 2);
		_text.setPosition(_background.getPosition().x + _background.getSize().x / 2,
			_background.getPosition().y + _background.getSize().y / 2);
	}
	else if (_alignment == "right") {
		_text.setOrigin(textBounds.width, 0);
		_text.setPosition(_background.getPosition().x + _background.getSize().x - 10, _background.getPosition().y);
	}
	else { // Default to left
		_text.setOrigin(0, 0);
		_text.setPosition(_background.getPosition().x + 10, _background.getPosition().y);
	}
}

void Noir2D::GUILabel::UpdateBackground()
{
	if (!_hasBackground) return;

	// Get text bounds properly
	sf::FloatRect textBounds = _text.getLocalBounds();

	// Set background size with padding
	_background.setSize(sf::Vector2f(textBounds.width + 20, textBounds.height + 20));
	_background.setFillColor(sf::Color(50, 50, 50, 150)); // Semi-transparent dark background

	// Adjust position to match text
	_background.setPosition(_text.getPosition().x - 10, _text.getPosition().y - 5);
}

void Noir2D::GUILabel::Draw(sf::RenderWindow& window) {
	if (_hasBackground) {
		window.draw(_background);
	}
	window.draw(_shadowText);
	window.draw(_text);
}

void Noir2D::GUILabel::SetHovered(bool hovered)
{

}

void Noir2D::GUILabel::Update(float deltaTime)
{
	if (_blinkEffect) {
		_elapsedTime += deltaTime;
		float alpha = static_cast<int>((sin(_elapsedTime * _blinkSpeed) * 0.5f + 0.5f) * 255);
		_text.setFillColor(sf::Color(_text.getFillColor().r, _text.getFillColor().g, _text.getFillColor().b, alpha));
	}
}

void Noir2D::GUILabel::UpdateLayout()
{
	auto& res = ResolutionManager::GetInstance();
	float scaleX = res.GetScaleX();
	float scaleY = res.GetScaleY();

	sf::Vector2f scaledPosition = { GetOriginalPosition().x * scaleX, GetOriginalPosition().y * scaleY};
	_text.setCharacterSize(static_cast<unsigned int>(_originalFontSize * scaleY));
	_text.setPosition(scaledPosition);

	if (_hasBackground) {
		sf::FloatRect bounds = _text.getGlobalBounds();
		_background.setSize({ bounds.width + 10.f, bounds.height + 10.f });
		_background.setFillColor(sf::Color(50, 50, 50, 150));
		_background.setPosition(scaledPosition.x - 5.f, scaledPosition.y - 5.f);
	}
}
