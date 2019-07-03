#include "SpelSyltPCH.h"

#include "RawAssetHelpers.h"

#include "RawAsset.h"
#include <SFML/Graphics/Texture.hpp>

//------------------------------------------------------------------

void SRawAssetHelpers::ToTexture(SRawAsset& InAsset, sf::Texture& OutTexture)
{
	OutTexture.loadFromMemory(InAsset.DataLocation, InAsset.DataSize);
}

//------------------------------------------------------------------

//------------------------------------------------------------------