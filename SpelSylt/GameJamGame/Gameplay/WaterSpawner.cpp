#include "WaterSpawner.h"
#include <SpelSylt/FileHandling/Asset/AssetManager.h>
#include <SpelSylt/Rendering/RenderQueue.h>
#include <SpelSylt/Rendering/RenderCommand.h>

#include <SpelSylt/Math/CommonMath.h>

tree::CWaterSpawner::CWaterSpawner(SpelSylt::CMessageQueue& aMessageQueue, SpelSylt::CAssetManager& aAssetManager, const CPawn& aPlayerPawn) : 
	myPlayerPawn(aPlayerPawn)
{
	myWater.SetTextureAsset(aAssetManager.GetAsset<SS::STextureAsset>("Graphics/Sprites/water.png"));
	myWater.setOrigin(32, 32);

	myTimer.Init(CTimedEvent::EType::Repeat, 5.f, [this]() {
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
	aRenderQueue.Enqueue(ERenderLayer::Game, SS::SSpriteRenderCommand(myWater));
}

void tree::CWaterSpawner::SpawnWater()
{
	float halfWidth = 1920.f / 2.f;
	float halfHeight = 1080.f / 2.f;

	float x = 1920.f * (rand() % 2) - halfWidth;
	float y = 1080.f * (rand() % 2) - halfHeight;

	myWater.setPosition(x - Math::Sign(x) * 32.f, y - Math::Sign(y) * 32.f);
}
