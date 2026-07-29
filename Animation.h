#pragma once
#include <SFML/Graphics.hpp>

namespace Noir2D
{
	class Animation
	{
	public:
		Animation(sf::Vector2i frameSize, int frameCount, float frameDuration);

		void Play();
		void Stop();
		void SetLooping(bool loop);
		void SetFrame(int index);
		void SetRow(int row);
		void Update(float deltaTime);
		sf::IntRect GetCurrentRect() const;
		bool IsPlaying() const;

	private:
		sf::Vector2i _frameSize;
		int _frameCount = 0;
		int _currentFrame = 0;
		int _row = 0;
		float _frameDuration = 0.f;
		float _elapsedTime = 0.f;
		bool _isPlaying = false;
		bool _loop = true;
	};
}
