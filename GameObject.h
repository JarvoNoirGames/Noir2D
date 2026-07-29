#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Animation.h"

namespace Noir2D
{
	class GameObject
	{
	public:
		GameObject(const sf::Texture& texture);
		virtual ~GameObject() = default;

		void SetAnimation(std::unique_ptr<Animation> animation);

		void SetPosition(const sf::Vector2f& pos);
		sf::Vector2f GetPosition() const;
		void SetScale(const sf::Vector2f& scale);
		void SetOrigin(const sf::Vector2f& origin);
		void Move(const sf::Vector2f& delta);
		sf::FloatRect GetBounds() const;

		virtual void Update(float deltaTime);
		virtual void Draw(sf::RenderWindow& window);

	protected:
		const sf::Texture* _texture = nullptr;
		sf::Sprite _sprite;
		std::unique_ptr<Animation> _animation;
	};
}
