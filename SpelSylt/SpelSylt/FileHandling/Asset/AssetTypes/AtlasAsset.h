#pragma once

#include "SpelSylt/FileHandling/Asset/AssetTypes/TextureAsset.h"
#include "SpelSylt/Rendering/Sprite/Sprite.h"

#include <SFML/Graphics/Rect.hpp>

#include <unordered_map>
#include <string>

namespace SpelSylt
{
	struct SAtlasAsset : public STextureAsset 
	{
	public:

		const std::unordered_map<std::string, sf::FloatRect>& GetRects() const { return myRects; }

	private:

		virtual void AssignData(char* InDataLocation, B InDataSize) override;

		B ReadTextureSizeFromHeader(char* InDataLocation);
		void ReadAtlasData(char* InDataLocation, B InDataSize);

		std::unordered_map<std::string, sf::FloatRect> myRects;

	};
}