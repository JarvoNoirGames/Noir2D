#include "Animation.h"

namespace Noir2D
{
	Animation::Animation(sf::Vector2i frameSize, int frameCount, float frameDuration)
		: _frameSize(frameSize), _frameCount(frameCount), _frameDuration(frameDuration)
	{

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
	}

	void Animation::SetLooping(bool loop)
	{
		_loop = loop;
	}

	void Animation::SetFrame(int index)
	{
		_currentFrame = index % _frameCount;
	}

	void Animation::SetRow(int row)
	{
		_row = row;
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
		}
	}

	sf::IntRect Animation::GetCurrentRect() const
	{
		int x = _currentFrame * _frameSize.x;
		int y = _row * _frameSize.y;
		return sf::IntRect(x, y, _frameSize.x, _frameSize.y);
	}

	bool Animation::IsPlaying() const
	{
		return _isPlaying;
	}
}
