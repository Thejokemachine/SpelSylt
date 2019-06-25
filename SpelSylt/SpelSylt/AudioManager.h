#pragma once
#include <string>
#include <unordered_map>

#include "SFML/Audio.hpp"

class AudioManager
{
public:
	AudioManager(const std::string& aAudioFolder);
	~AudioManager() = default;

	void Update();

	void PlaySound(const std::string& aAlias, sf::Sound* aSoundHandle = nullptr);

private:

	std::unordered_map<std::string, sf::SoundBuffer> mySoundBuffers;
	std::vector<sf::Sound> mySoundHandles;
};