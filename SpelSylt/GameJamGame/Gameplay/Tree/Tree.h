#pragma once
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

	class CTree
	{
	public:
		CTree(SS::CMessageQueue& aMsgQueue, SS::CAssetManager& aAssetManager, CPawn& aPlayerPawn);
		~CTree();

		void Render(SS::CRenderQueue& aRenderQueue);

	private:

		std::array<SS::CSprite, 5> mySprites;
		int myWaterLevel = 0;
		short myCurrentLevel = 0;

		CPawn& myPlayerPawn;

		SS::CMessageQueue& myMsgQueue;
		SS::CSubscriptions mySubs;
	};
}