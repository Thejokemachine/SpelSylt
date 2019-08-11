#include "EngineTestProject/EngineTestProjectState.h"

#include <SpelSylt/Contexts/GameContext.h>
#include "EngineTestProject/System/TestSystem.h"
#include <SpelSylt/FileHandling/Asset/AssetManager.h>

//------------------------------------------------------------------

using namespace testproj;

//------------------------------------------------------------------

void testproj::CTestProjectState::OnInit(SS::SGameContext& InGameContext)
{
	Systems.EmplaceSystem<CTestSystem>(InGameContext.AssetManager);
}

//------------------------------------------------------------------

void testproj::CTestProjectState::OnUpdate(SS::SGameContext& InGameContext)
{
}

//------------------------------------------------------------------

void testproj::CTestProjectState::OnRender(SS::CRenderQueue& InRenderQueue)
{
}

//------------------------------------------------------------------