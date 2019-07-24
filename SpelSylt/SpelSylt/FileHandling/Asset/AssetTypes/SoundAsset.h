#pragma once

#include "SpelSylt/FileHandling/Asset/Asset.h"

#include <SFML/Audio/SoundBuffer.hpp>

struct SSoundAsset final
	: public SBaseAsset
	, sf::SoundBuffer
{
	SSoundAsset()
		: SBaseAsset()
		, sf::SoundBuffer()
	{
	}

private:
	virtual void AssignData(char* InDataLocation, B InDataSize) override
	{
		loadFromMemory(InDataLocation, InDataSize);
	}

};