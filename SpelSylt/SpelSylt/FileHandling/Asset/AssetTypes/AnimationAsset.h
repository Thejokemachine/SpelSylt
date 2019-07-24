#pragma once

#include "SpelSylt/FileHandling/Asset/Asset.h"
#include "SpelSylt/FileHandling/Asset/AssetTypes/TextureAsset.h"

namespace SpelSylt
{
	struct SAnimationFrame
	{
		float Time;
		unsigned int X, Y, W, H;
	};

	struct SAnimationData
	{
		SAnimationData()
			: Frames(nullptr)
			, FrameCount(0)
			, NextFrame(0)
		{}

		void Allocate(unsigned int InFrameCount)
		{
			if (Frames != nullptr)
			{
				delete[FrameCount] Frames;
			}

			FrameCount = InFrameCount;
			Frames = new SAnimationFrame[FrameCount];
		}

		void AddFrame(const SAnimationFrame& InFrame)
		{
			memcpy_s(&Frames[NextFrame], sizeof(SAnimationFrame), &InFrame, sizeof(SAnimationFrame));
		}

		SAnimationFrame* Frames;
		unsigned int FrameCount;
		unsigned int NextFrame;
	};

	struct SAnimationAsset final
		: public STextureAsset
	{
	private:
		/*
		SpelSylt Anim file
		Header 4B - Specifying size of the anim image
		Image
		AnimationData
		*/

		virtual void AssignData(char* InDataLocation, B InDataSize) override;
		virtual void ReadAnimData(char* InDataLocation, B InDataSize);
		B ReadHeader(char* InDataLocation);

		SAnimationData AnimData;

	};
}

namespace SS = SpelSylt;