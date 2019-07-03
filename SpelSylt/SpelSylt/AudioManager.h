#pragma once
#include <string>
#include <unordered_map>

#include "Assets.h"

#include "SFML/Audio.hpp"

class IAsyncLoader;

class AudioManager
{
public:
	AudioManager(const std::string& aAudioFolder);
	~AudioManager() = default;

	void LoadSounds(IAsyncLoader& InAsyncLoader, const std::string& InAudioFolder);
	void Update(const float dt);

	void PlaySound(const std::string& aAlias, sf::Sound* aSoundHandle = nullptr);
	void PlayMusic(const std::string& aAlias, bool aFadeOutCurrent);

private:

	std::unordered_map<std::string, SSoundAsset> mySoundBuffers;
	std::vector<sf::Sound*> mySoundHandles;

	sf::Music myMusic;
	float myMusicFade = 0.f;
	std::string myMusicAlias;
	bool myShouldSwitchMusic = false;
};