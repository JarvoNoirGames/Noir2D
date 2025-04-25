#pragma once
#include "GUIElement.h"
#include "ResolutionManager.h"
#include <SFML/Graphics.hpp>
#include <string>

namespace Noir2D
{
    class GUITextbox : public GUIElement 
    {
    public:
        GUITextbox(const sf::Vector2f& position, const sf::Vector2f& size, sf::Font& font,
            const std::string& text = "", unsigned int fontSize = 24,
            const sf::Color& textColor = sf::Color::White,
            const sf::Color& backgroundColor = sf::Color(0, 0, 0, 180),
            const sf::Color& outlineColor = sf::Color::White,
            float outlineThickness = 2.0f);

        void SetText(const std::string& text);
        void SetTypingEnabled(bool enabled);
        void SetTypingSpeed(float charactersPerSecond);
        void SkipTyping();
        bool IsTyping() const;
        void Update(float deltaTime) override;
        void Draw(sf::RenderWindow& window) override;
        void UpdateLayout() override;
        void CompleteText();
        void HandleEvent(const sf::Event& event, const sf::Vector2f& mousePos) override;
        float GetFontSize();
        void SetFontSize(const float size);
        std::string WrapTextToFit(const std::string& text, float maxWidth);
        std::vector<std::string> SplitTextIntoWords(const std::string& text);

    private:
        sf::RectangleShape _box;
        sf::Text _text;
        sf::Font& _font;

        std::string _fullText;
        std::string _displayedText;

        float _typingSpeed = 50.0f; // Characters per second
        float _typingTimer = 0.0f;
        bool _typingEnabled = true;
        bool _isTyping = false;
        float _fontSize = 24.f;
        sf::Vector2f _padding = { 10.f, 10.f };  // Padding for the text inside the box
    };
}