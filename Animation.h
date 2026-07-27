#pragma once
#include <SFML/Graphics.hpp>

namespace Noir2D
{
	class Animation
	{
	public:
		Animation(const sf::Texture& texture, sf::Vector2i frameSize, int frameCount, float frameDuration);

		void Play();
		void Stop();
		void SetLooping(bool loop);
		void SetFrame(int index);
		void SetRow(int row);

		void SetPosition(const sf::Vector2f& pos);
		void SetScale(const sf::Vector2f& scale);
		void SetOrigin(const sf::Vector2f& origin);

		void Update(float deltaTime);
		void Draw(sf::RenderWindow& window);

	private:
		void UpdateFrame();

		const sf::Texture& _texture;
		sf::Sprite _sprite;
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
