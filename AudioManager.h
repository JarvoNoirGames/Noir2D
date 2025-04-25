#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>

namespace Noir2D
{
    class AudioManager
    {
    public:
        static AudioManager& GetInstance()
        {
            static AudioManager instance;
            return instance;
        }

        // Background music
        void PlayMusic(const std::string& filename, bool loop = true);
        void StopMusic();
        void SetMusicVolume(float volume);
        float GetMusicVolume() const;

        // Sound effects
        void PlaySound(const std::string& name);
        void LoadSound(const std::string& name, const std::string& filepath);
        void SetSoundVolume(float volume);
        float GetSoundVolume() const;

    private:
        AudioManager() = default;

        sf::Music _music;
        float _musicVolume = 100.0f;

        std::unordered_map<std::string, sf::SoundBuffer> _soundBuffers;
        std::vector<sf::Sound> _activeSounds;
        float _soundVolume = 100.0f;
    };
}

