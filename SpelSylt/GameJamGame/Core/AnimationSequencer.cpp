#include "GameJamGame/Core/AnimationSequencer.h"

#include <SpelSylt/Rendering/RenderQueue.h>
#include <SpelSylt/FileHandling/Asset/AssetManager.h>
#include <SpelSylt/FileHandling/Asset/AssetTypes/AnimationAsset.h>

#include <SpelSylt/Rendering/RenderCommand.h>

//------------------------------------------------------------------

using namespace tree;

std::unordered_map<std::string, std::vector<SS::CSpriteAnimation>> CAnimationSequencer::Animations;
SpelSylt::CAssetManager* CAnimationSequencer::AssetManager;

//------------------------------------------------------------------

CAnimationSequencer::CAnimationSequencer(SpelSylt::CAssetManager& InAssetManager)
{
	AssetManager = &InAssetManager;
}

//------------------------------------------------------------------

void CAnimationSequencer::PlayAnimationAtPosition(const char* InAnimation, const sf::Vector2f& InPosition)
{
	Animations[InAnimation].emplace_back();
	SS::CSpriteAnimation& NewAnimation = Animations[InAnimation].back();
	NewAnimation.SetPlayType(SS::EAnimationPlayType::OneShot);
	NewAnimation = AssetManager->GetAsset<SS::SAnimationAsset>(InAnimation);
	NewAnimation.setPosition(InPosition);
}

//------------------------------------------------------------------

void CAnimationSequencer::Update(float aDT)
{
	for (auto& AnimationMapPair : Animations)
	{
		auto& AnimationList = AnimationMapPair.second;

		std::vector<int> ToRemove;
		ToRemove.reserve(AnimationList.size());

		for (int i = 0; i < AnimationList.size(); ++i)
		{
			auto& Animation = AnimationList[i];

			Animation.Tick(aDT);

			if (Animation.IsFinished())
			{
				ToRemove.push_back(i);
			}
		}

		int PreviouslyRemoved = 0;
		for (int RemoveIndex : ToRemove)
		{
			RemoveIndex -= PreviouslyRemoved;
			AnimationList.erase(AnimationList.begin() + RemoveIndex);
			PreviouslyRemoved++;
		}
	}
}

//------------------------------------------------------------------

void CAnimationSequencer::Render(SpelSylt::CRenderQueue& aRenderQueue)
{
	for (auto& AnimationMapPair : Animations)
	{
		auto& AnimationList = AnimationMapPair.second;
		for (auto& Animation : AnimationList)
		{
			aRenderQueue.Enqueue(ERenderLayer::Game, SS::SSpriteAnimationRenderCommand(Animation));
		}
	}
}

//------------------------------------------------------------------