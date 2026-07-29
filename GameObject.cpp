#include "GameObject.h"

namespace Noir2D
{
	GameObject::GameObject(const sf::Texture& texture)
		: _texture(&texture)
	{
		_sprite.setTexture(*_texture);
	}

	void GameObject::SetAnimation(std::unique_ptr<Animation> animation)
	{
		_animation = std::move(animation);
		if (_animation)
			_sprite.setTextureRect(_animation->GetCurrentRect());
	}

	void GameObject::SetPosition(const sf::Vector2f& pos)
	{
		_sprite.setPosition(pos);
	}

	sf::Vector2f GameObject::GetPosition() const
	{
		return _sprite.getPosition();
	}

	void GameObject::SetScale(const sf::Vector2f& scale)
	{
		_sprite.setScale(scale);
	}

	void GameObject::SetOrigin(const sf::Vector2f& origin)
	{
		_sprite.setOrigin(origin);
	}

	void GameObject::Move(const sf::Vector2f& delta)
	{
		_sprite.move(delta);
	}

	sf::FloatRect GameObject::GetBounds() const
	{
		return _sprite.getGlobalBounds();
	}

	void GameObject::Update(float deltaTime)
	{
		if (_animation)
		{
			_animation->Update(deltaTime);
			_sprite.setTextureRect(_animation->GetCurrentRect());
		}
	}

	void GameObject::Draw(sf::RenderWindow& window)
	{
		window.draw(_sprite);
	}
}