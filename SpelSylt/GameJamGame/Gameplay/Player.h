#pragma once
#include "GameJamGame/Gameplay/Pawn.h"

namespace tree
{
	class CPlayer : public CPawn
	{
	public:
		virtual void Tick(float InDT) override;

	private:

	};
}