#pragma once
#include <SFML/Graphics.hpp>

namespace Noir2D
{
	class Collision
	{
	public:
		static bool Intersects(const sf::FloatRect& a, const sf::FloatRect& b);
	};
}