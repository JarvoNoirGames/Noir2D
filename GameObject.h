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
		void SetVelocity(const sf::Vector2f& velocity);
		sf::Vector2f GetVelocity() const;
		void SetStatic(bool isStatic);
		bool IsStatic() const;
		void SetGravityScale(float scale);
		float GetGravityScale() const;
		void SetFriction(float friction);
		float GetFriction() const;
		virtual void Update(float deltaTime);
		virtual void Draw(sf::RenderWindow& window);

	protected:
		const sf::Texture* _texture = nullptr;
		sf::Sprite _sprite;
		std::unique_ptr<Animation> _animation;
		sf::Vector2f _velocity;
		bool _isStatic = false;
		float _gravityScale = 0.f; // 0 = unaffected by world gravity
		float _friction = 0.f;     // 0 = no velocity damping
	};
}
