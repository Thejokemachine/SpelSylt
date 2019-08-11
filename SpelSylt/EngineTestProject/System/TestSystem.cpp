#include "EngineTestProject/System/TestSystem.h"

#include <SpelSylt/FileHandling/Asset/AssetManager.h>
#include <SpelSylt/FileHandling/Asset/AssetTypes/TextureAsset.h>
#include <SpelSylt/Rendering/RenderQueue.h>
#include <SpelSylt/Rendering/RenderCommand.h>

//------------------------------------------------------------------

using namespace testproj;

//------------------------------------------------------------------

CTestSystem::CTestSystem(SpelSylt::CAssetManager& InAssetManager)
	: DirRight(true)
{
	TestSystemSprite = InAssetManager.GetAsset<SS::STextureAsset>("Graphics/Sprites/TestSprite.png");
}

//------------------------------------------------------------------

void CTestSystem::Tick(float InDT)
{
	const float HighLimit = 500.f;
	const float LowLimit = 200.f;

	if (DirRight)
	{
		Pos.x += 200.f * InDT;
		if (Pos.x > HighLimit)
		{
			DirRight = false;
		}
	}
	else
	{
		Pos.x -= 200.f * InDT;
		if (Pos.x < LowLimit)
		{
			DirRight = true;
		}
	}

	TestSystemSprite.setPosition(Pos);
}

//------------------------------------------------------------------

void CTestSystem::Render(SpelSylt::CRenderQueue& InRenderQueue)
{
	InRenderQueue.Enqueue(ERenderLayer::Game, SS::SSpriteRenderCommand(TestSystemSprite));
}

//------------------------------------------------------------------