#pragma once

#include "GameJamGame/Gameplay/Enemy/EnemyPawn.h"

namespace SpelSylt
{
	struct SGameContext;
}

namespace tree
{
	class CEnemy
	{
	public:
		CEnemy();

		void Update(SpelSylt::SGameContext& InGameContext);

		const CEnemyPawn& GetPawn() const;
		CEnemyPawn& GetPawn();

	private:
		CEnemyPawn Pawn;

		bool CanAttack(float InDT);

		float TimeToNextAttack;
		float TimeBetweenAttacks;
	};
}