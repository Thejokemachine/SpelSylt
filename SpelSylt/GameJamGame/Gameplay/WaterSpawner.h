#pragma once
#include "GameJamGame/Core/System.h"

#include <SpelSylt/Rendering/Sprite/Sprite.h>
#include <SpelSylt/Utility/TimedEvent.h>

namespace SpelSylt
{
	class CAssetManager;
	class CRenderQueue;
	class CMessageQueue;
}

namespace tree
{
	class CPawn;

	class CWaterSpawner : public ISystem
	{
	public:
		CWaterSpawner(SpelSylt::CMessageQueue& aMessageQueue, SpelSylt::CAssetManager& aAssetManager, const CPawn& aPlayerPawn);

		virtual void Update(float aDT) override;

		virtual void Render(SpelSylt::CRenderQueue& aRenderQueue) override;

	private:

		void SpawnWater();

		CTimedEvent myTimer;
		SS::CSprite myWater;


		const CPawn& myPlayerPawn;
	};
}