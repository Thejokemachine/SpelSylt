#include "GameJamGame/States/TreeGameState.h"

#include "GameJamGame/Gameplay/Controller/InputController.h"

#include <SpelSylt/Contexts/GameContext.h>
#include <SpelSylt/Contexts/RenderingContext.h>

#include <SpelSylt/Utility/Time/TimeGetter.h>
#include <SpelSylt/FileHandling/ConfigReader.h>
#include <SpelSylt/FileHandling/FileWatcher.h>

//------------------------------------------------------------------

using namespace tree;

//------------------------------------------------------------------

void CTreeGameState::OnInit(SS::SGameContext& InGameContext)
{
	PlayerPawn.AttachController(Controllers.CreateInputController(InGameContext.Input));

	ReadPlayerPawnSpeedFromConfig();

	SS::CFileWatcher::AddFile("player.cfg", [this] { ReadPlayerPawnSpeedFromConfig(); });
}

//------------------------------------------------------------------

void CTreeGameState::OnUpdate(SS::SGameContext& InGameContext)
{
	Controllers.Update();
	PlayerPawn.Tick(InGameContext.Time.GetDeltaTime());
}

//------------------------------------------------------------------

void CTreeGameState::OnRender(SS::CRenderQueue& InRenderQueue)
{
	myDebugDrawer.DrawCircle(PlayerPawn.GetPosition(), 32.f, true, sf::Color::Green);
}

//------------------------------------------------------------------

void CTreeGameState::ReadPlayerPawnSpeedFromConfig()
{
	SS::CConfigReader ConfigReader;
	ConfigReader.ReadConfigFile("player.cfg");

	PlayerPawn.SetSpeed(ConfigReader.GetAsFloat("speed"));
}

//------------------------------------------------------------------