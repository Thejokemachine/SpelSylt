#pragma once
#include "GameJamGame/Gameplay/Pawn.h"

#include <SpelSylt/Rendering/Animation/SpriteAnimation.h>
#include <SpelSylt/Rendering/Sprite/Sprite.h>

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
		SS::CSpriteAnimation StandingAnimation;
		SS::CSpriteAnimation* ActiveAnimation;
		
		SS::CSpriteAnimation CrosshairAnimation;

		SS::CSprite ArmSprite;
		SS::CSprite ShadowSprite;

		SpelSylt::IInputEventGetter& InputManager;

	};
}