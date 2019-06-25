#include "AudioManager.h"

#include <filesystem>
#include <iostream>

AudioManager::AudioManager(const std::string & aAudioFolder)
{
	for (auto&& file : std::filesystem::directory_iterator(aAudioFolder + "Sounds/"))
	{
		std::string alias = file.path().stem().string();
		std::string fileName = file.path().string();
		mySoundBuffers[alias].loadFromFile(fileName);
	}
}

void AudioManager::Update()
{
	for (int i = 0; i < mySoundHandles.size(); ++i)
	{
		if (mySoundHandles[i].getStatus() != sf::Sound::Playing)
		{
			mySoundHandles[i] = mySoundHandles.back();
			mySoundHandles.pop_back();
		}
	}
}

void AudioManager::PlaySound(const std::string& aAlias, sf::Sound * aSoundHandle)
{
	if (mySoundBuffers.find(aAlias) != mySoundBuffers.end())
	{
		if (aSoundHandle)
		{
			aSoundHandle->setBuffer(mySoundBuffers.at(aAlias));
			aSoundHandle->play();
		}
		else
		{
			mySoundHandles.push_back(sf::Sound());
			mySoundHandles.back().setBuffer(mySoundBuffers.at(aAlias));
			mySoundHandles.back().play();
		}
	}
}
