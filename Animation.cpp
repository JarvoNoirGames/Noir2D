#include "Animation.h"

namespace Noir2D
{
	Animation::Animation(const sf::Texture& texture, sf::Vector2i frameSize, int frameCount, float frameDuration)
		: _texture(texture), _frameSize(frameSize), _frameCount(frameCount), _frameDuration(frameDuration)
	{
		_sprite.setTexture(_texture);
		UpdateFrame();
	}

	void Animation::Play()
	{
		_isPlaying = true;
	}

	void Animation::Stop()
	{
		_isPlaying = false;
		_currentFrame = 0;
		_elapsedTime = 0.f;
		UpdateFrame();
	}

	void Animation::SetLooping(bool loop)
	{
		_loop = loop;
	}

	void Animation::SetFrame(int index)
	{
		_currentFrame = index % _frameCount;
		UpdateFrame();
	}

	void Animation::SetRow(int row)
	{
		_row = row;
		UpdateFrame();
	}

	void Animation::SetPosition(const sf::Vector2f& pos)
	{
		_sprite.setPosition(pos);
	}

	void Animation::SetScale(const sf::Vector2f& scale)
	{
		_sprite.setScale(scale);
	}

	void Animation::SetOrigin(const sf::Vector2f& origin)
	{
		_sprite.setOrigin(origin);
	}

	void Animation::Update(float deltaTime)
	{
		if (!_isPlaying)
			return;

		_elapsedTime += deltaTime;

		while (_elapsedTime >= _frameDuration)
		{
			_elapsedTime -= _frameDuration;
			_currentFrame++;

			if (_currentFrame >= _frameCount)
			{
				if (_loop)
					_currentFrame = 0;
				else
				{
					_currentFrame = _frameCount - 1;
					_isPlaying = false;
				}
			}

			UpdateFrame();
		}
	}

	void Animation::Draw(sf::RenderWindow& window)
	{
		window.draw(_sprite);
	}

	void Animation::UpdateFrame()
	{
		int x = _currentFrame * _frameSize.x;
		int y = _row * _frameSize.y;
		_sprite.setTextureRect(sf::IntRect(x, y, _frameSize.x, _frameSize.y));
	}
}
