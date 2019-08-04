#include "Tree.h"

#include <SpelSylt/Messaging/MessageQueue.h>

#include <SpelSylt/FileHandling/Asset/AssetManager.h>
#include <SpelSylt/FileHandling/Asset/AssetTypes/TextureAsset.h>

#include <SpelSylt/Rendering/RenderQueue.h>
#include <SpelSylt/Rendering/RenderCommand.h>

#include <SpelSylt/Math/CommonMath.h>

#include "GameJamGame/Gameplay/Pawn.h"
#include "GameJamGame/Core/GameMessages.h"

using namespace tree;

CTree::CTree(SS::CMessageQueue & aMsgQueue, SS::CAssetManager& aAssetManager, const CPawn& aPawn) : 
	myMsgQueue(aMsgQueue),
	myPlayerPawn(aPawn),
	myLevelProgressions{
		0, 4, 12, 24, 40
	}
{
	for (int i = 0; i < mySprites.size(); ++i)
	{
		mySprites[i].SetTextureAsset(aAssetManager.GetAsset<SS::STextureAsset>((std::string("Graphics/Sprites/tree_")+std::to_string(i)+".png").c_str()));
		mySprites[i].setOrigin(256, 512);
	}

	myMsgQueue.Subscribe<WaterMsg>([this](const auto& msg) {
		float distToPlayer = Math::Length2(myPlayerPawn.GetPosition());
		if (distToPlayer < 100.f * 100.f)
		{
			myWaterLevel += 1;
			for (int i = 0; i < myLevelProgressions.size(); ++i)
			{
				if (myWaterLevel >= myLevelProgressions[i])
					myCurrentLevel = i;
			}

			float currentReq = myLevelProgressions[myCurrentLevel];
			float nextReq = myLevelProgressions[myCurrentLevel + 1];
			float totalThisLevelReq = nextReq - currentReq;
			float current = myWaterLevel - myLevelProgressions[myCurrentLevel];
			myMsgQueue.DispatchEvent<WaterLevelMsg>(current / totalThisLevelReq);
			myMsgQueue.DispatchEvent<TreeLevelMsg>(myCurrentLevel+1);
		}
	}, mySubs);

	myMsgQueue.Subscribe<TreeAttackedMsg>([this](const auto & msg) {
		myCurrentLevel = Math::Clamp(myCurrentLevel - 1, 0, 4);
	}, mySubs);
}

tree::CTree::~CTree()
{
}

void tree::CTree::Render(SS::CRenderQueue & aRenderQueue)
{
	aRenderQueue.Enqueue(ERenderLayer::Foreground, SS::SSpriteRenderCommand(mySprites[myCurrentLevel]));
}
