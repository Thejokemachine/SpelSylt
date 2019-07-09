#pragma once

#include "SpelSylt/FileHandling/Asset/Asset.h"

#include <SFML/Graphics/Texture.hpp>

struct STextureAsset
	: public SBaseAsset
	, public sf::Texture
{
	STextureAsset()
		: SBaseAsset()
		, sf::Texture()
	{
	}

protected:
	virtual void AssignData(char* InDataLocation, B InDataSize) override
	{
		loadFromMemory(InDataLocation, InDataSize);
	}
};