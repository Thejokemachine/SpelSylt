#include "GameJamGame/Gameplay/Enemy/Enemy.h"

#include "GameJamGame/Core/GameMessages.h"

#include <SpelSylt/Contexts/GameContext.h>

#include <SpelSylt/Utility/Time/Time.h>
#include <SpelSylt/Messaging/MessageQueue.h>

//------------------------------------------------------------------

using namespace tree;

//------------------------------------------------------------------

CEnemy::CEnemy()
	: Pawn()
	, TimeToNextAttack(0.f)
	, TimeBetweenAttacks(5.f)
{
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
		Pawn.Tick(DT);
	}
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

