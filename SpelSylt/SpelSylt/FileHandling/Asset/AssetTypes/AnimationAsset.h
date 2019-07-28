#pragma once

#include "SpelSylt/FileHandling/Asset/Asset.h"
#include "SpelSylt/FileHandling/Asset/AssetTypes/TextureAsset.h"

#include <string>
#include <vector>

namespace SpelSylt
{
	struct SAnimationFrame
	{
		SAnimationFrame(
			float InTime,
			unsigned int InX,
			unsigned int InY,
			unsigned int InW,
			unsigned int InH )
			: Time(InTime)
			, X(InX)
			, Y(InY)
			, W(InW)
			, H(InH)
		{
		}

		float Time;
		unsigned int X, Y, W, H;
	};

	struct SAnimationData
	{
		SAnimationData()
			: Frames()
		{}

		std::vector<SAnimationFrame> Frames;
	};

	struct SAnimationAsset final
		: public STextureAsset
	{
	public:
		const SAnimationData& GetAnimationData() const;
	private:
		virtual void AssignData(char* InDataLocation, B InDataSize) override;

		B ReadTextureSizeFromHeader(char* InDataLocation);
		void ReadTextureData(char* InDataLocation, B InDataSize);
		void ReadAnimData(char* InDataLocation, B InDataSize);

		SAnimationData AnimData;
	};
}

namespace SS = SpelSylt;