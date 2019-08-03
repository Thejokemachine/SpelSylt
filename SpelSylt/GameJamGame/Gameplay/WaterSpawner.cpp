#include "WaterSpawner.h"
#include <SpelSylt/FileHandling/Asset/AssetManager.h>
#include <SpelSylt/Rendering/RenderQueue.h>
#include <SpelSylt/Rendering/RenderCommand.h>

tree::CWaterSpawner::CWaterSpawner(SpelSylt::CAssetManager & aAssetManager)
{
	myWaterTexture = aAssetManager.GetAsset<SS::STextureAsset>("Graphics/Sprites/water.png");

	myTimer.Init(CTimedEvent::EType::Repeat, 15.f, [this]() {
		SpawnWater();
	});
	myTimer.Start();
}

void tree::CWaterSpawner::Update(float aDT)
{
	myTimer.Update(aDT);
}

void tree::CWaterSpawner::Render(SpelSylt::CRenderQueue & aRenderQueue)
{
	SS::CSprite rc;
	rc.SetTextureAsset(myWaterTexture);
	rc.setOrigin(32, 32);

	aRenderQueue.Enqueue(ERenderLayer::Game, SS::SSpriteRenderCommand(rc));
}

void tree::CWaterSpawner::SpawnWater()
{
}
