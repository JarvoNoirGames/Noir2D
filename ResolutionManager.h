#pragma once
#include "DEFINITIONS.h"
#include <SFML/Graphics.hpp>

namespace Noir2D
{
    class ResolutionManager {
    public:
        static ResolutionManager& GetInstance();

        void SetBaseResolution(const sf::Vector2u& base);
        void SetWindowSize(const sf::Vector2u& current);

        float GetScaleX() const;
        float GetScaleY() const;

        const sf::Vector2u& GetBaseResolution() const;
        const sf::Vector2u& GetCurrentWindowSize() const;

    private:
        ResolutionManager() = default;

        sf::Vector2u _baseResolution = { SCREEN_WIDTH, SCREEN_HEIGHT };
        sf::Vector2u _currentWindowSize = { SCREEN_WIDTH, SCREEN_HEIGHT };
    };
}