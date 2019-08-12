#include "SpelSylt/SpelSyltPCH.h"
#include "AtlasAsset.h"
#include "SpelSylt/../RapidJsonLibrary/JsonDocument.h"

void SpelSylt::SAtlasAsset::AssignData(char * InDataLocation, B InDataSize)
{
	const B HeaderOffset = 8;
	const B TextureSize = ReadTextureSizeFromHeader(InDataLocation);
	STextureAsset::AssignData(&InDataLocation[HeaderOffset], TextureSize);

	const B AtlasDataOffset = HeaderOffset + TextureSize;
	const B AtlasDataSize = InDataSize - AtlasDataOffset;
	ReadAtlasData(&InDataLocation[AtlasDataOffset], AtlasDataSize);
}

B SpelSylt::SAtlasAsset::ReadTextureSizeFromHeader(char * InDataLocation)
{
	B TextureSize = 0;
	memcpy_s(&TextureSize, sizeof(B), InDataLocation, 8);
	return TextureSize;
}

void SpelSylt::SAtlasAsset::ReadAtlasData(char * InDataLocation, B InDataSize)
{
	JsonDocument DataAsJson;
	DataAsJson.LoadFromMemory(InDataLocation, InDataSize);

	if (DataAsJson.Find("textures"))
	{
		auto&& textures = DataAsJson["textures"];
		size_t textureCount = textures.GetSize();
		myRects.reserve(textureCount);

		for (size_t i = 0; i < textureCount; ++i)
		{
			JsonValue&& obj = textures[static_cast<int>(i)];

			const std::string id = obj["id"].GetString();
			float x = obj["x"].GetFloat();
			float y = obj["y"].GetFloat();
			float w = obj["w"].GetFloat();
			float h = obj["h"].GetFloat();

			myRects.insert_or_assign(id, sf::FloatRect(x, y, w, h));
		}
	}
}
