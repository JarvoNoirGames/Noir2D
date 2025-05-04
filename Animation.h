#pragma once
#include <SFML/Graphics.hpp>

namespace Noir2D
{
	class Animation
	{
	public:
		Animation(const sf::Texture& texture, sf::Vector2i frameSize, const std::vector<int>& rowFrameCounts, float frameDuration);

		void Play();
		void Stop();
		void SetLooping(bool loop);
		void SetFrame(int index);

		void Update(float deltaTime);
		void Draw(sf::RenderWindow& window);

		void SetPosition(const sf::Vector2f& pos);
		sf::Vector2f GetPosition() const;

		void SetScale(const sf::Vector2f& scale);
		sf::Sprite& GetSprite();

		void SetRow(int row);

	private:
		const sf::Texture& _texture;
		sf::Sprite _sprite;
		std::vector<int> _rowFrameCounts;
		sf::Vector2i _frameSize;
		int _frameCount = 0;
		int _currentFrame = 0;
		int _row = 0;
		float _frameDuration = 0.f;
		float _elapsedTime = 0.f;
		
		bool _isPlaying = false;
		bool _loop = true;

		void UpdateFrame();
	};
}
