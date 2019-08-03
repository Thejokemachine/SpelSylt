#pragma once
#include "GameJamGame/Core/System.h"

#include <SpelSylt/Rendering/Sprite/Sprite.h>
#include <SpelSylt/Utility/TimedEvent.h>
#include <SpelSylt/Messaging/Subscribing/Subscriptions.h>

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
		void DespawnWater();

		bool myIsPaused;

		CTimedEvent myTimer;
		SS::CSprite myWater;

		SS::CSubscriptions mySubs;

		const CPawn& myPlayerPawn;
	};
}