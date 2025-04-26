#include "AudioManager.h"

void Noir2D::AudioManager::Update()
{
	// Clean up finished sounds
	_activeSounds.erase(
		std::remove_if(_activeSounds.begin(), _activeSounds.end(),
			[](const std::shared_ptr<sf::Sound>& sound) { return sound->getStatus() == sf::Sound::Stopped; }),
		_activeSounds.end()
	);
}

void Noir2D::AudioManager::PlayMusic(const std::string& filename, bool loop)
{
	_music.stop();
	if (_music.openFromFile(filename))
	{
		_music.setLoop(loop);
		_music.setVolume(_musicVolume);
		_music.play();
	}
}

void Noir2D::AudioManager::StopMusic()
{
	_music.stop();
}

void Noir2D::AudioManager::SetMusicVolume(float volume)
{
	_musicVolume = volume;
	_music.setVolume(volume);
}

float Noir2D::AudioManager::GetMusicVolume() const
{
	return _musicVolume;
}

void Noir2D::AudioManager::PlaySound(const std::string& name)
{
	auto iter = _soundBuffers.find(name);
	if (iter == _soundBuffers.end())
		return;

	auto sound = std::make_shared<sf::Sound>(iter->second);
	sound->setVolume(_soundVolume);
	sound->play();
	_activeSounds.push_back(sound);
}

void Noir2D::AudioManager::LoadSound(const std::string& name, const std::string& filepath)
{
	sf::SoundBuffer buffer;
	if (buffer.loadFromFile(filepath))
	{
		_soundBuffers[name] = buffer;
	}
}

void Noir2D::AudioManager::SetSoundVolume(float volume)
{
	_soundVolume = volume;
}

float Noir2D::AudioManager::GetSoundVolume() const
{
	return _soundVolume;
}
