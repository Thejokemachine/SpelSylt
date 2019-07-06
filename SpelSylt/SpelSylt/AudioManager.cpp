#include "SpelSyltPCH.h"

#include "AudioManager.h"

#include "CommonMath.h"

#include <iostream>

#include "DirectoryHelpers.h"

CAudioManager::CAudioManager(const std::string & aAudioFolder)
{
}

void CAudioManager::Init(CMessageQueue& InMessageQueue)
{
	const auto& MusicMessageCallback = [&](const SMusicMessage & InMessage) { OnMusicMessage(InMessage); };
	InMessageQueue.Subscribe<SMusicMessage>(MusicMessageCallback, Subscriptions);

	const auto& SoundMessageCallback = [&](const SSoundMessage & InMessage) {OnSoundMessage(InMessage); };
	InMessageQueue.Subscribe<SSoundMessage>(SoundMessageCallback, Subscriptions);

	LoadSounds("Audio/");
}

void CAudioManager::LoadSounds(/*IAsyncLoader& InAsyncLoader,*/ const std::string& InAudioFolder)
{
	std::string SoundsFolder = InAudioFolder + "Sounds/";

	//TODO: If needed this can now be loaded async
	SDirectoryHelpers::VisitDirectory(
		SoundsFolder.c_str(),
		[&](const FFile & InFile) {
			std::string alias = InFile.path().stem().string();
			std::string fileName = InFile.path().string();
			
			mySoundBuffers[alias].loadFromFile(fileName);
		});
}

void CAudioManager::Update(const float dt)
{
	for (int i = 0; i < mySoundHandles.size(); ++i)
	{
		if (mySoundHandles[i]->getStatus() != sf::Sound::Playing)
		{
			mySoundHandles[i] = mySoundHandles.back();
			mySoundHandles.pop_back();
		}
	}

	if (myShouldSwitchMusic)
	{
		myMusicFade -= dt / 3.f;
		if (myMusicFade <= 0.f)
		{
			myShouldSwitchMusic = false;
			myMusic.stop();
			myMusic.openFromFile("Audio/Music/" + myMusicAlias);
			myMusic.play();
		}
	}
	else
	{
		myMusicFade += dt / 3.f;
	}
	myMusicFade = Math::Clamp(myMusicFade, 0.f, 1.f);
	myMusic.setVolume(myMusicFade * 100.f);
}

void CAudioManager::PlaySound(const std::string& aAlias, sf::Sound * aSoundHandle)
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
			mySoundHandles.push_back(new sf::Sound());
			mySoundHandles.back()->setBuffer(mySoundBuffers.at(aAlias));
			mySoundHandles.back()->play();
		}
	}
}

void CAudioManager::PlayMusic(const std::string & aAlias, bool aFadeOutCurrent)
{
	if (myMusicAlias != aAlias)
	{
		myMusicAlias = aAlias;
		if (!aFadeOutCurrent)
		{
			myMusic.stop();
			myMusic.openFromFile("Audio/Music/" + myMusicAlias + ".ogg");
			myMusic.play();
		}
		else
		{
			myShouldSwitchMusic = true;
		}
	}
}

void CAudioManager::OnMusicMessage(const SMusicMessage& InMessage)
{
	PlayMusic(InMessage.Alias, InMessage.FadeOutCurrent);
}

void CAudioManager::OnSoundMessage(const SSoundMessage& InMessage)
{
	PlaySound(InMessage.Alias);
}