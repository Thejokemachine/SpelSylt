#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/Rendering/Sprite/Sprite.h"
#include "SpelSylt/Rendering/Animation/SpriteAnimation.h"
#include "SpelSylt/FileHandling/Asset/AssetTypes/AnimationAsset.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

using namespace SpelSylt;

//------------------------------------------------------------------

CSpriteAnimation::CSpriteAnimation()
	: TimeUntilNextFrame(0.f)
	, CurrentFrame(0)
	, MaxFrames(0)
	, AnimationAsset(nullptr)
	, DataLoaded(false)
{
}

//------------------------------------------------------------------

void CSpriteAnimation::operator=(const CSpriteAnimation& InRHS)
{
	AnimationAsset = InRHS.AnimationAsset;
	TimeUntilNextFrame = InRHS.TimeUntilNextFrame;
	CurrentFrame = InRHS.CurrentFrame;
	MaxFrames = InRHS.MaxFrames;
	DataLoaded = InRHS.DataLoaded;
}

//------------------------------------------------------------------

void CSpriteAnimation::operator=(const SAnimationAsset& InRHS)
{
	AnimationAsset = &InRHS;
}

//------------------------------------------------------------------

void CSpriteAnimation::Tick(float InDeltaTime)
{
	if (!DataLoaded)
	{
		if (AnimationAsset->GetLoadStatus() != ELoadRequestStatus::Done || AnimationAsset->GetLoadStatus() == ELoadRequestStatus::Fail)
		{
			return;
		}

		//We can load the Data
		LoadData();
	}

	TimeUntilNextFrame -= InDeltaTime;

	if (TimeUntilNextFrame <= 0.f)
	{
		IncrementFrame();
	}
}

//------------------------------------------------------------------

void CSpriteAnimation::draw(sf::RenderTarget& InTarget, sf::RenderStates InStates) const
{
	if (!DataLoaded)
	{
		return;
	}

	const SAnimationFrame& CurrentFrameData = AnimationAsset->GetAnimationData().Frames[CurrentFrame];

	CSprite Sprite;
	Sprite.SetTextureAsset(*AnimationAsset);
	Sprite.setTextureRect(sf::IntRect(CurrentFrameData.X, CurrentFrameData.Y, CurrentFrameData.W, CurrentFrameData.H));
	Sprite.setPosition(getPosition());
	Sprite.setOrigin(getOrigin());
	Sprite.setColor(getColor());

	Sprite.draw(InTarget, InStates);
}

//------------------------------------------------------------------

void CSpriteAnimation::LoadData()
{
	const SAnimationData& AnimationData = AnimationAsset->GetAnimationData();
	MaxFrames = static_cast<unsigned int>(AnimationData.Frames.size());
	TimeUntilNextFrame = AnimationData.Frames[CurrentFrame].Time;
	DataLoaded = true;
}

//------------------------------------------------------------------

void CSpriteAnimation::IncrementFrame()
{
	CurrentFrame++;
	CurrentFrame %= MaxFrames;
	TimeUntilNextFrame = AnimationAsset->GetAnimationData().Frames[CurrentFrame].Time;
}

//------------------------------------------------------------------