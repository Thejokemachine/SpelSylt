#include "SpelSylt/SpelSyltPCH.h"
#include "SpelSylt/../RapidJsonLibrary/JsonDocument.h"
#include "SpelSylt/FileHandling/Asset/AssetTypes/AnimationAsset.h"

using namespace SpelSylt;

//------------------------------------------------------------------

const SAnimationData& SAnimationAsset::GetAnimationData() const
{
	return AnimData;
}

//------------------------------------------------------------------

void SAnimationAsset::AssignData(char* InDataLocation, B InDataSize)
{
	const B HeaderOffset = 8;
	const B TextureSize = ReadTextureSizeFromHeader(InDataLocation);
	ReadTextureData(&InDataLocation[HeaderOffset], TextureSize);//InDataLocation, InDataSize); //&InDataLocation[HeaderOffset], TextureSize);

	const B AnimDataOffset = HeaderOffset + TextureSize;
	const B AnimDataSize = InDataSize - AnimDataOffset;
	ReadAnimData(InDataLocation + AnimDataOffset, AnimDataSize);
}

//------------------------------------------------------------------

B SAnimationAsset::ReadTextureSizeFromHeader(char* InDataLocation)
{
	B TextureSize = 0;
	memcpy_s(&TextureSize, sizeof(B), InDataLocation, 8);
	return TextureSize;
}

//------------------------------------------------------------------

void SAnimationAsset::ReadTextureData(char* InDataLocation, B InDataSize)
{
	STextureAsset::AssignData(InDataLocation, InDataSize);
}

//------------------------------------------------------------------

void SAnimationAsset::ReadAnimData(char* InDataLocation, B InDataSize)
{
	JsonDocument DataAsJson;
	DataAsJson.LoadFromMemory(InDataLocation, InDataSize);

	if (DataAsJson.Find("frames"))
	{
		unsigned int FrameCount = static_cast<unsigned int>(DataAsJson["frames"].GetSize());
		AnimData.Frames.reserve(FrameCount);

		for (unsigned int i = 0; i < FrameCount; ++i)
		{
			JsonValue Obj = DataAsJson["frames"][i];

			float Time = Obj["time"].GetFloat();
			unsigned int X = static_cast<unsigned int>(Obj["x"].GetInt());
			unsigned int Y = static_cast<unsigned int>(Obj["y"].GetInt());
			unsigned int W = static_cast<unsigned int>(Obj["w"].GetInt());
			unsigned int H = static_cast<unsigned int>(Obj["h"].GetInt());

			AnimData.Frames.emplace_back(Time, X, Y, W, H);
		}
	}

}

//------------------------------------------------------------------