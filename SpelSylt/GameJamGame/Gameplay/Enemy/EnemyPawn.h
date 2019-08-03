#pragma once
#include "GameJamGame/Gameplay/Pawn.h"

namespace tree
{
	class CEnemyPawn
		: public CPawn
	{
	public:
		CEnemyPawn();
		virtual void Tick(float InDT) override;

		bool HasReachedTarget() const;
	private:
		bool ReachedTarget : 1;
	};
}