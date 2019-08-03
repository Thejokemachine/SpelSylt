#pragma once
#include <string>
#include <unordered_map>

#include "SpelSylt/FileHandling/Asset/Assets.h"
#include "SpelSylt/Messaging/Subscribing/Subscriptions.h"

#include "SFML/Audio.hpp"

namespace SpelSylt
{
	class CMessageQueue;
    class ILoader;

	struct SMusicMessage;
	struct SSoundMessage;

	class CAudioManager
	{
	public:
		CAudioManager();
		~CAudioManager() = default;

		void Init(CMessageQueue& InMessageQueue);

		void LoadSounds(/*IAsyncLoader& InAsyncLoader,*/ const std::string& InAudioFolder);
		void Update(const float dt);

		void PlaySound(const std::string& aAlias, sf::Sound* aSoundHandle = nullptr);
		void PlayMusic(const std::string& aAlias, bool aFadeOutCurrent);

	private:
		void OnMusicMessage(const SMusicMessage& InMessage);
		void OnSoundMessage(const SSoundMessage& InMessage);

		std::unordered_map<std::string, SSoundAsset> mySoundBuffers;
		std::vector<sf::Sound*> mySoundHandles;

		sf::Music myMusic;
		float myMusicFade = 0.f;
		std::string myMusicAlias;
		bool myShouldSwitchMusic = false;
		float myMusicVolume = 5.f;

		CSubscriptions Subscriptions;
	};
}

namespace SS = SpelSylt;