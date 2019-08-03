#pragma once

#include <SpelSylt/GameState2D.h>

#include "GameJamGame/Gameplay/Controller/ControllerContainer.h"
#include "GameJamGame/Gameplay/Player.h"

#include "GameJamGame/Gameplay/Tree/Tree.h"

namespace tree
{
	class CTreeGameState
		: public SS::GameState2D
	{
	private:
		virtual void OnInit(SS::SGameContext& InGameContext) override;
		virtual void OnUpdate(SS::SGameContext& InGameContext) override;
		virtual void OnRender(SS::CRenderQueue& InRenderQueue) override;

		void ReadPlayerPawnSpeedFromConfig();

		CPlayer PlayerPawn;
		CControllerContainer Controllers;

		std::unique_ptr<CTree> Tree = nullptr;
		SS::CSprite AreaBG;
	};
}