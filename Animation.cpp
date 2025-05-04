#include "Animation.h"

	Noir2D::Animation::Animation(const sf::Texture& texture, sf::Vector2i frameSize, const std::vector<int>& rowFrameCounts, float frameDuration)
		: _texture(texture), _frameSize(frameSize), _rowFrameCounts(rowFrameCounts), _frameDuration(frameDuration)
	{
		_sprite.setTexture(_texture);
		SetRow(0);
	}

	void Noir2D::Animation::Play()
	{
		_isPlaying = true;
		_elapsedTime = 0.f;
	}

	void Noir2D::Animation::Stop()
	{
		_isPlaying = false;
	}

	void Noir2D::Animation::SetLooping(bool loop)
	{
		_loop = loop;
	}

	void Noir2D::Animation::SetFrame(int index)
	{
		if (index >= 0 && index < _frameCount)
		{
			_currentFrame = index;
			UpdateFrame();
		}
	}

	void Noir2D::Animation::Update(float deltaTime)
	{
		if (!_isPlaying) return;

		_elapsedTime += deltaTime;
		if (_elapsedTime >= _frameDuration)
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

	void Noir2D::Animation::UpdateFrame()
	{
		int columns = _texture.getSize().x / _frameSize.x;
		int x = (_currentFrame % columns) * _frameSize.x;
		int y = _row * _frameSize.y;//Row selection
		_sprite.setTextureRect(sf::IntRect(x, y, _frameSize.x, _frameSize.y));
	}

	void Noir2D::Animation::Draw(sf::RenderWindow& window)
	{
		window.draw(_sprite);
	}

	void Noir2D::Animation::SetPosition(const sf::Vector2f& pos)
	{
		_sprite.setPosition(pos);
	}

	sf::Vector2f Noir2D::Animation::GetPosition() const
	{
		return _sprite.getPosition();
	}

	void Noir2D::Animation::SetScale(const sf::Vector2f& scale)
	{
		_sprite.setScale(scale);
	}

	sf::Sprite& Noir2D::Animation::GetSprite()
	{
		return _sprite;
	}

	void Noir2D::Animation::SetRow(int row)
	{
		if (row >= 0 && row < static_cast<int>(_rowFrameCounts.size()))
		{
			_row = row;
			_frameCount = _rowFrameCounts[row];
			_currentFrame = 0;
			_elapsedTime = 0.f;
			UpdateFrame();
		}
	}
