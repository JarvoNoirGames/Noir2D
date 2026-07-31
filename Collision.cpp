#include "Collision.h"
namespace Noir2D
{
	bool Collision::Intersects(const sf::FloatRect& a, const sf::FloatRect& b)
	{
		return a.intersects(b);
	}
}