#pragma once

#include <SpelSylt/GameState2D.h>

#include "GameJamGame/Gameplay/Controller/ControllerContainer.h"
#include "GameJamGame/Gameplay/Player.h"

#include "GameJamGame/Core/System.h"

#include "GameJamGame/Gameplay/World/WorldState.h"
#include "GameJamGame/Gameplay/World/ProbeConstructor.h"

namespace tree
{
	class CTreeGameState
		: public SS::GameState2D
	{
	public:
		CTreeGameState();
	private:
		virtual void OnInit(SS::SGameContext& InGameContext) override;
		virtual void OnUpdate(SS::SGameContext& InGameContext) override;
		virtual void OnRender(SS::CRenderQueue& InRenderQueue) override;

		void ReadPlayerPawnSpeedFromConfig();

		CProbeConstructor ProbeConstructor;
		CControllerContainer Controllers;

		CPlayer PlayerPawn;
		FWorldObjectID PlayerWorldObjectID;

		CPawn EnemyPawn;

		std::vector<std::unique_ptr<ISystem>> Systems;

		SS::CSprite AreaBG;

		CWorldState WorldState;
	};
}