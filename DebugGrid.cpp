#include "DebugGrid.h"

namespace Noir2D
{
	DebugGrid::DebugGrid(int worldWidth, int worldHeight, int cellSize)
		: _lines(sf::Lines)
	{
		sf::Color lineColor(80, 80, 80);

		for (int x = 0; x <= worldWidth; x += cellSize)
		{
			_lines.append(sf::Vertex(sf::Vector2f((float)x, 0.f), lineColor));
			_lines.append(sf::Vertex(sf::Vector2f((float)x, (float)worldHeight), lineColor));
		}

		for (int y = 0; y <= worldHeight; y += cellSize)
		{
			_lines.append(sf::Vertex(sf::Vector2f(0.f, (float)y), lineColor));
			_lines.append(sf::Vertex(sf::Vector2f((float)worldWidth, (float)y), lineColor));
		}
	}

	void DebugGrid::Draw(sf::RenderWindow& window) const
	{
		window.draw(_lines);
	}
}