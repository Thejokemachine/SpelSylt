#include "SpelSylt/SpelSyltPCH.h"
#include "Atlas.h"
#include "SpelSylt/FileHandling/Asset/AssetTypes/AtlasAsset.h"

SpelSylt::CAtlas::CAtlas()
{
}

void SpelSylt::CAtlas::operator=(const CAtlas & InRHS)
{
	AtlasAsset = InRHS.AtlasAsset;
}

void SpelSylt::CAtlas::operator=(SAtlasAsset& InRHS)
{
	AtlasAsset = &InRHS;
}

CSprite SpelSylt::CAtlas::BuildSprite(const std::string & InTextureID) const
{
	CSprite newSprite;
	newSprite = *AtlasAsset;

	int textureSize = AtlasAsset->GetSize().x;

	auto&& rects = AtlasAsset->GetRects();

	if (rects.find(InTextureID) != rects.end())
	{
		auto&& rect = rects.at(InTextureID);
		newSprite.setTextureRect(sf::IntRect((int)(rect.left * textureSize), (int)(rect.top * textureSize), (int)(rect.width * textureSize), (int)(rect.height * textureSize)));
		newSprite.setOrigin(newSprite.getGlobalBounds().width * 0.5f, newSprite.getGlobalBounds().height * 0.5f);
	}

	return newSprite;
}
