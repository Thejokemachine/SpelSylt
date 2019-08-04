#pragma once
#include "GameJamGame/Gameplay/Pawn.h"

#include <SpelSylt/Rendering/Animation/SpriteAnimation.h>

namespace SpelSylt
{
	class CRenderQueue;
	class CAssetManager;
	class IInputEventGetter;
}

namespace tree
{
	class CPlayer : public CPawn
	{
	public:
		CPlayer(SpelSylt::CAssetManager& InAssetManager, SpelSylt::IInputEventGetter& InInputManager);

		virtual void Tick(float InDT) override;
		void Draw(SpelSylt::CRenderQueue& InRenderQueue);
	private:
		SS::CSpriteAnimation RunningAnimation;
		SpelSylt::IInputEventGetter& InputManager;

	};
}