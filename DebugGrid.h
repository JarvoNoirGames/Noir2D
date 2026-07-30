#pragma once
#include <SFML/Graphics.hpp>

namespace Noir2D
{
	class DebugGrid
	{
	public:
		DebugGrid(int worldWidth, int worldHeight, int cellSize);
		void Draw(sf::RenderWindow& window) const;

	private:
		sf::VertexArray _lines;
	};
}