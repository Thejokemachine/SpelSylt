#pragma once
#include "GameJamGame/Core/System.h"
#include "SpelSylt/Rendering/Sprite/Sprite.h"
#include "SpelSylt/Messaging/Subscribing/Subscriptions.h"

#include <array>

namespace SpelSylt
{
	class CRenderQueue;
	class CMessageQueue;
	class CAssetManager;
}

namespace tree
{
	class CPawn;

	class CTree : public ISystem
	{
	public:
		CTree(SS::CMessageQueue& aMsgQueue, SS::CAssetManager& aAssetManager, const CPawn& aPlayerPawn);
		~CTree();

		virtual void Render(SS::CRenderQueue& aRenderQueue) override;

	private:

		std::array<SS::CSprite, 5> mySprites;
		int myWaterLevel = 0;
		short myCurrentLevel = 0;

		const CPawn& myPlayerPawn;

		SS::CMessageQueue& myMsgQueue;
		SS::CSubscriptions mySubs;
	};
}