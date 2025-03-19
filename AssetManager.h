#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>

namespace Noir2D
{
	class AssetManager
	{
	public:
		static AssetManager& GetInstance();  // Singleton
		AssetManager() {}
		~AssetManager() {}

		void LoadTexture(const std::string& name, const std::string& fileName);
		const sf::Texture& GetTexture(const std::string& name) const;

		void LoadFont(const std::string& name, const std::string& fileName);
		const sf::Font& GetFont(const std::string& name) const;

		void LoadSound(const std::string& name, const std::string& fileName);
		const sf::SoundBuffer& GetSound(const std::string& name) const;

		void Cleanup();
	private:
		std::unordered_map<std::string, sf::Texture> _textures;
		std::unordered_map<std::string, sf::Font> _fonts;
		std::unordered_map<std::string, sf::SoundBuffer> _sounds;
	};
}
