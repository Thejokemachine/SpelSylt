#include "WaterSpawner.h"
#include <SpelSylt/FileHandling/Asset/AssetManager.h>
#include <SpelSylt/Rendering/RenderQueue.h>
#include <SpelSylt/Rendering/RenderCommand.h>

#include <SpelSylt/Math/CommonMath.h>
#include <SpelSylt/Messaging/MessageQueue.h>

#include "GameJamGame/Core/GameMessages.h"
#include "GameJamGame/Gameplay/Pawn.h"

tree::CWaterSpawner::CWaterSpawner(SpelSylt::CMessageQueue& aMessageQueue, SpelSylt::CAssetManager& aAssetManager, const CPawn& aPlayerPawn) :
	myPlayerPawn(aPlayerPawn),
	myIsPaused(false)
{
	myWater.SetTextureAsset(aAssetManager.GetAsset<SS::STextureAsset>("Graphics/Sprites/water.png"));
	myWater.setOrigin(32, 32);

	myTimer.Init(CTimedEvent::EType::Repeat, 3.f, [this]() {
		SpawnWater();
		myIsPaused = true;
	});
	myTimer.Start();

	aMessageQueue.Subscribe<InteractMsg>([this, &aMessageQueue](const auto& msg) {
		sf::Vector2f toPlayer = myPlayerPawn.GetPosition() - myWater.getPosition();
		if (Math::Length2(toPlayer) < 64.f * 64.f)
		{
			DespawnWater();
			aMessageQueue.DispatchEvent<PickedUpWater>();
			myIsPaused = false;
		}
	}, mySubs);
}

void tree::CWaterSpawner::Update(float aDT)
{
	if (!myIsPaused)
	{
		myTimer.Update(aDT);
	}
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

void tree::CWaterSpawner::DespawnWater()
{
	myWater.setPosition(-10000, -10000);
}