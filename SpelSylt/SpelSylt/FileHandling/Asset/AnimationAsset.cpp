#include "SpelSylt/SpelSyltPCH.h"
#include "SpelSylt/../RapidJsonLibrary/JsonDocument.h"
#include "SpelSylt/FileHandling/Asset/AnimationAsset.h"

#define ANIMATION_HEADER_OFFSET_BYTES 8ull

//------------------------------------------------------------------

void SAnimationAsset::AssignData(char* InDataLocation, B InDataSize)
{
	const B SizeOfAnimationImg = ReadHeader(InDataLocation);
	char* AnimImgLocation = InDataLocation + ANIMATION_HEADER_OFFSET_BYTES;
	STextureAsset::AssignData(AnimImgLocation, SizeOfAnimationImg);
	
	const B SizeOfAnimData = InDataSize - (SizeOfAnimationImg + ANIMATION_HEADER_OFFSET_BYTES);
	char* AnimDataLocation = AnimImgLocation + SizeOfAnimationImg;
	ReadAnimData(AnimDataLocation, SizeOfAnimData);
}

//------------------------------------------------------------------

B SAnimationAsset::ReadHeader(char* InDataLocation)
{
	B OffsetData = 0; //0x0000
	memcpy_s(&OffsetData, sizeof(B), InDataLocation, ANIMATION_HEADER_OFFSET_BYTES);
	return OffsetData;
}

//------------------------------------------------------------------

void SAnimationAsset::ReadAnimData(char* InDataLocation, B InDataSize)
{
	JsonDocument DataAsJson;
	DataAsJson.LoadFromMemory(InDataLocation, InDataSize);

	if (DataAsJson.Find("frames"))
	{
		unsigned int FrameCount = static_cast<unsigned int>(DataAsJson["frames"].GetSize());
		AnimData.Allocate(FrameCount);

		for (unsigned int i = 0; i < FrameCount; ++i)
		{
			JsonValue Obj = DataAsJson["frames"][i];

			SAnimationFrame BuiltFrame;
			BuiltFrame.Time = Obj["time"].GetFloat();
			BuiltFrame.X = static_cast<unsigned int>(Obj["x"].GetInt());
			BuiltFrame.Y = static_cast<unsigned int>(Obj["y"].GetInt());
			BuiltFrame.W = static_cast<unsigned int>(Obj["w"].GetInt());
			BuiltFrame.H = static_cast<unsigned int>(Obj["h"].GetInt());

			AnimData.AddFrame(BuiltFrame);
		}
	}

}

//------------------------------------------------------------------