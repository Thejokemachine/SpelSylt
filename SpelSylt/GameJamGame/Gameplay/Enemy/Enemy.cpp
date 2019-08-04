#include "GameJamGame/Gameplay/Enemy/Enemy.h"

#include "GameJamGame/Core/GameMessages.h"

#include <SpelSylt/Contexts/GameContext.h>

#include <SpelSylt/Utility/Time/Time.h>
#include <SpelSylt/Messaging/MessageQueue.h>

#include <SpelSylt/FileHandling/Asset/AssetManager.h>
#include <SpelSylt/FileHandling/Asset/AssetTypes/AnimationAsset.h>
#include <SpelSylt/FileHandling/Asset/AssetTypes/TextureAsset.h>
#include <SpelSylt/Rendering/RenderCommand.h>
#include <SpelSylt/Rendering/RenderQueue.h>

#include "GameJamGame/Gameplay/Pawn.h"
#include "GameJamGame/Gameplay/Controller/ControllerInterface.h"

//------------------------------------------------------------------

using namespace tree;

//------------------------------------------------------------------

CEnemy::CEnemy(SpelSylt::CAssetManager& InAssetManager)
	: Pawn()
	, TimeToNextAttack(0.f)
	, TimeBetweenAttacks(5.f)
{
	WalkAnimation = InAssetManager.GetAsset<SS::SAnimationAsset>("Graphics/Animations/zombie.anmbndl");
	ShadowSprite.SetTextureAsset(InAssetManager.GetAsset<SS::STextureAsset>("Graphics/Sprites/shadow.png"));
	ShadowSprite.setOrigin({ 32.f, 28.f });
	WalkAnimation.setOrigin({ 32.f, 32.f });
}

//------------------------------------------------------------------

void CEnemy::Update(SpelSylt::SGameContext& InGameContext)
{
	const float DT = InGameContext.Time.GetDeltaTime();

	if (Pawn.HasReachedTarget() && CanAttack(DT))
	{
		InGameContext.MessageQueue.DispatchEvent<TreeAttackedMsg>();
	}
	else
	{
		WalkAnimation.Tick(DT);
		Pawn.Tick(DT);
	}
}

//------------------------------------------------------------------

void CEnemy::Render(SpelSylt::CRenderQueue& InRenderQueue)
{

	ShadowSprite.setPosition(Pawn.GetPosition());
	InRenderQueue.Enqueue(ERenderLayer::Game, SS::SSpriteRenderCommand(ShadowSprite));

	const float MoveX = Pawn.GetController().GetVelocity().x;
	if (MoveX < 0.f)
	{
		WalkAnimation.setScale(-1.f, 1.f);
	}
	else if (MoveX > 0.f)
	{
		WalkAnimation.setScale(1.f, 1.f);
	}
	WalkAnimation.setPosition(Pawn.GetPosition());
	InRenderQueue.Enqueue(ERenderLayer::Game, SS::SSpriteAnimationRenderCommand(WalkAnimation));
}

//------------------------------------------------------------------

const CEnemyPawn& tree::CEnemy::GetPawn() const
{
	return Pawn;
}

//------------------------------------------------------------------

CEnemyPawn& tree::CEnemy::GetPawn()
{
	return Pawn;
}

//------------------------------------------------------------------

bool CEnemy::CanAttack(float InDT)
{
	TimeToNextAttack -= InDT;
	if (TimeToNextAttack <= 0.f)
	{
		TimeToNextAttack = TimeBetweenAttacks;
		return true;
	}

	return false;
}

//------------------------------------------------------------------

