#include "GameJamGame/States/TreeGameState.h"

#include "GameJamGame/Gameplay/Controller/InputController.h"

#include <SpelSylt/Contexts/GameContext.h>
#include <SpelSylt/Contexts/RenderingContext.h>

#include <SpelSylt/Utility/Time/TimeGetter.h>

//------------------------------------------------------------------

using namespace tree;

//------------------------------------------------------------------

void CTreeGameState::OnInit(SS::SGameContext& InGameContext)
{
	TestPawn.AttachController(Controllers.CreateInputController(InGameContext.Input));
	TestPawn.SetSpeed(128.f);
}

//------------------------------------------------------------------

void CTreeGameState::OnUpdate(SS::SGameContext& InGameContext)
{
	Controllers.Update();
	TestPawn.Tick(InGameContext.Time.GetDeltaTime());
}

//------------------------------------------------------------------

void tree::CTreeGameState::OnRender(SS::CRenderQueue& InRenderQueue)
{
	myDebugDrawer.DrawCircle(TestPawn.GetPosition(), 32.f, true, sf::Color::Green);
}

//------------------------------------------------------------------