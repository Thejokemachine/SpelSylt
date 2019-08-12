#pragma once
#include "SpelSylt/Rendering/Sprite/Sprite.h"

namespace SpelSylt
{
	struct SAtlasAsset;

	class CAtlas
	{
	public:
		CAtlas();

		void operator=(const CAtlas& InRHS);
		void operator=(SAtlasAsset& InRHS);

		CSprite BuildSprite(const std::string& aTextureID) const;

	private:
		const SAtlasAsset* AtlasAsset = nullptr;
	};
}

namespace SS = SpelSylt;