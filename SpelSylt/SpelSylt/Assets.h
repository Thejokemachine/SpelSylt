#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include "MemAllocSizes.h"

struct SBaseAsset
{
	friend class CAsyncLoader;

	SBaseAsset()
	{}

protected:
	void SetData(char* InDataLocation, B InDataSize)
	{
		AssignData(InDataLocation, InDataSize);
	}
	
	virtual void AssignData(char* InDataLocation, B InDataSize) = 0;
};

struct STextureAsset final
	: public SBaseAsset
	, public sf::Texture
{
	STextureAsset()
		: SBaseAsset()
		, sf::Texture()
	{
	}

private:
	virtual void AssignData(char* InDataLocation, B InDataSize) override
	{
		loadFromMemory(InDataLocation, InDataSize);
	}
};

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