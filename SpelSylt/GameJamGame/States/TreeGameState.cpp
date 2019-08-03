#include "GameJamGame/States/TreeGameState.h"

#include "GameJamGame/Gameplay/Controller/InputController.h"
#include "GameJamGame/Core/GameMessages.h"

#include <SpelSylt/Contexts/GameContext.h>
#include <SpelSylt/Contexts/RenderingContext.h>
#include <SpelSylt/FileHandling/Asset/AssetManager.h>

#include <SpelSylt/Messaging/MessageQueue.h>
#include <SpelSylt/Utility/Time/TimeGetter.h>
#include <SpelSylt/FileHandling/ConfigReader.h>
#include <SpelSylt/FileHandling/FileWatcher.h>
#include <SpelSylt/Math/CommonMath.h>

#include "GameJamGame/Gameplay/Tree/Tree.h"
#include "GameJamGame/Gameplay/WaterSpawner.h"
#include "GameJamGame/Gameplay/Inventory/Inventory.h"

//------------------------------------------------------------------

using namespace tree;

//------------------------------------------------------------------

void CTreeGameState::OnInit(SS::SGameContext& InGameContext)
{
	Systems.emplace_back(std::make_unique<CTree>(InGameContext.MessageQueue, InGameContext.AssetManager, PlayerPawn));
	Systems.emplace_back(std::make_unique<CWaterSpawner>(InGameContext.MessageQueue, InGameContext.AssetManager, PlayerPawn));
	Systems.emplace_back(std::make_unique<CInventory>(InGameContext.MessageQueue));
	
	PlayerPawn.AttachController(Controllers.CreateInputController(InGameContext.Input, InGameContext.MessageQueue));

	ReadPlayerPawnSpeedFromConfig();

	SS::CFileWatcher::AddFile("player.cfg", [this] { ReadPlayerPawnSpeedFromConfig(); });

	GetCamera().setCenter({ 0,0 });
	GetCamera().setSize(1920.f, 1080.f);

	AreaBG.SetTextureAsset(InGameContext.AssetManager.GetAsset<SS::STextureAsset>("Graphics/Sprites/area.png"));
	AreaBG.setOrigin(960, 540);
}

//------------------------------------------------------------------

void CTreeGameState::OnUpdate(SS::SGameContext& InGameContext)
{
	for (auto& system : Systems)
	{
		system->Update(InGameContext.Time.GetDeltaTime());
	}

	Controllers.Update();
	PlayerPawn.Tick(InGameContext.Time.GetDeltaTime());

	if (Math::Length2(PlayerPawn.GetPosition()) < 100 * 100.f)
	{
		InGameContext.MessageQueue.DispatchEvent<ShowWaterPrompt>();
	}
	else
	{
		InGameContext.MessageQueue.DispatchEvent<HideWaterPrompt>();
	}

	myDebugDrawer.DrawCircle({}, 100.f, false, sf::Color::Blue);
}

//------------------------------------------------------------------

void CTreeGameState::OnRender(SS::CRenderQueue& InRenderQueue)
{
	for (auto& system : Systems)
	{
		system->Render(InRenderQueue);
	}
	InRenderQueue.Enqueue(ERenderLayer::Background, SS::SSpriteRenderCommand(AreaBG));

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