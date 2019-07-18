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

	sf::Vector2u GetSize() const
	{
		if (LoadStatus != ELoadRequestStatus::Done)
		{
			return sf::Vector2u(64, 64);
		}

		return getSize();
	}

	const sf::Texture& GetNormalMap() const { return NormalMap; };

protected:
	virtual void AssignData(char* InDataLocation, B InDataSize) override
	{
		loadFromMemory(InDataLocation, InDataSize);
		NormalMap.loadFromFile("Graphics/Sprites/Player_NM.png");
	}

private:
	sf::Texture NormalMap;
};