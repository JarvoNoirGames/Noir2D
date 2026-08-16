#include "AssetManager.h"
#include "PathUtils.h"
#include <iostream>

namespace Noir2D
{
	AssetManager& AssetManager::GetInstance() {
		static AssetManager instance;
		return instance;
	}

    void AssetManager::LoadTexture(const std::string& name, const std::string& filename) {
        if (_textures.find(name) != _textures.end()) return;
        std::string resolvedPath = PathUtils::ResolveAssetPath(filename);
        if (!_textures[name].loadFromFile(resolvedPath)) {
            std::cerr << "Error loading texture: " << resolvedPath << std::endl;
            _textures.erase(name);
        }
    }

    void AssetManager::LoadFont(const std::string& name, const std::string& filename) {
        if (_fonts.find(name) != _fonts.end()) return;
        std::string resolvedPath = PathUtils::ResolveAssetPath(filename);
        if (!_fonts[name].loadFromFile(resolvedPath)) {
            std::cerr << "Error loading font: " << resolvedPath << std::endl;
            _fonts.erase(name);
        }
    }

    void AssetManager::LoadSound(const std::string& name, const std::string& filename) {
        if (_sounds.find(name) != _sounds.end()) return;
        std::string resolvedPath = PathUtils::ResolveAssetPath(filename);
        if (!_sounds[name].loadFromFile(resolvedPath)) {
            std::cerr << "Error loading sound: " << resolvedPath << std::endl;
            _sounds.erase(name);
        }
    }

    const sf::Texture& AssetManager::GetTexture(const std::string& name) const {
        return _textures.at(name);
    }

    const sf::Font& AssetManager::GetFont(const std::string& name) const {
        return _fonts.at(name);
    }

    const sf::SoundBuffer& AssetManager::GetSound(const std::string& name) const {
        return _sounds.at(name);
    }
    void AssetManager::Cleanup()
    {
        _textures.clear();
        _fonts.clear();
        _sounds.clear();
    }
}