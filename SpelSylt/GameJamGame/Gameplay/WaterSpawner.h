#pragma once
#include <SpelSylt/FileHandling/Asset/AssetTypes/TextureAsset.h>
#include <SpelSylt/Utility/TimedEvent.h>

namespace SpelSylt
{
	class CAssetManager;
	class CRenderQueue;
}

namespace tree
{
	class CWaterSpawner
	{
	public:
		CWaterSpawner(SpelSylt::CAssetManager& aAssetManager);

		void Update(float aDT);

		void Render(SpelSylt::CRenderQueue& aRenderQueue);

	private:

		void SpawnWater();

		CTimedEvent myTimer;
		SS::STextureAsset myWaterTexture;
	};
}