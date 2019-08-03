#include "GameJamGame/Gameplay/Enemy/EnemySpawner.h"

#include <SpelSylt/Rendering/Sprite/Sprite.h>
#include <SpelSylt/Rendering/RenderCommand.h>
#include <SpelSylt/Rendering/RenderQueue.h>

#include "GameJamGame/Gameplay/Controller/ControllerContainer.h"

//------------------------------------------------------------------

using namespace tree;

//------------------------------------------------------------------

CEnemySpawner::CEnemySpawner(CControllerContainer& InControllerContainer)
{
	TimeBetweenSpawns = 5.f;
	TimeUntilNextSpawn = 0.f;
	NextSimpleEnemy = 0;

	SimpleEnemyList.reserve(MAX_SIMPLE_ENEMY_TYPE);

	for (int i = 0; i < MAX_SIMPLE_ENEMY_TYPE; ++i)
	{
		SimpleEnemyList.emplace_back();
		SimpleEnemyList.back().AttachController(InControllerContainer.CreateAIController());
		SimpleEnemyList.back().SetSpeed(64.f);
	}
}

//------------------------------------------------------------------

void CEnemySpawner::SetTexture(SS::CTexture& InTexture)
{
	SimpleEnemyTexture = InTexture;
}

//------------------------------------------------------------------

void CEnemySpawner::Update(float InDT)
{
	TimeUntilNextSpawn -= InDT;

	if (TimeUntilNextSpawn <= 0.f)
	{
		SpawnEnemy();
	}

	for (CPawn* ActiveEnemyPawn : ActiveEnemies)
	{
		ActiveEnemyPawn->Tick(InDT);
	}
}

//------------------------------------------------------------------

void CEnemySpawner::Render(SpelSylt::CRenderQueue& aRenderQueue)
{
	SS::CSprite Sprite;
	Sprite.SetTextureAsset(SimpleEnemyTexture.Get());

	for (CPawn* ActiveEnemyPawn : ActiveEnemies)
	{
		Sprite.setPosition(ActiveEnemyPawn->GetPosition());
		aRenderQueue.Enqueue(ERenderLayer::Game, SS::SSpriteRenderCommand(Sprite));
	}
}

//------------------------------------------------------------------

void CEnemySpawner::SpawnEnemy()
{
	TimeUntilNextSpawn = TimeBetweenSpawns;

	CPawn& NextEnemy = SimpleEnemyList[NextSimpleEnemy];
	NextSimpleEnemy++;

	NextEnemy.SetPositon({ 1920.f / 2.f, 1080.f / 2.f }); //Todo: Should be random

	ActiveEnemies.push_back(&NextEnemy);
}

//------------------------------------------------------------------