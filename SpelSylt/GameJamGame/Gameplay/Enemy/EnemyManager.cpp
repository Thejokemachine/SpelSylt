#include "GameJamGame/Gameplay/Enemy/EnemyManager.h"

#include <SpelSylt/Rendering/Sprite/Sprite.h>
#include <SpelSylt/Rendering/RenderCommand.h>
#include <SpelSylt/Rendering/RenderQueue.h>
#include <SpelSylt/Contexts/GameContext.h>
#include <SpelSylt/Messaging/MessageQueue.h>

#include <SpelSylt/Physics/Collision/CircleCollider.h>
#include <SpelSylt/Physics/Collision/PointCollider.h>
#include <SpelSylt/Math/CommonMath.h>
#include <SpelSylt/FileHandling/Asset/AssetManager.h>
#include <SpelSylt/FileHandling/Asset/AssetTypes/AnimationAsset.h>

#include "GameJamGame/Gameplay/Controller/ControllerContainer.h"

#include "GameJamGame/Core/WindowDefines.h"

#include <SpelSylt/Debugging/Logging/DebugLogger.h>

#include "GameJamGame/Core/AnimationSequencer.h"

//------------------------------------------------------------------

using namespace tree;

//------------------------------------------------------------------

CEnemyManager::CEnemyManager(CControllerContainer& InControllerContainer, SpelSylt::SGameContext& InGameContext)
	: GameContext(InGameContext)
{
	TimeBetweenSpawns = 5.f;
	TimeUntilNextSpawn = 0.f;
	NextSimpleEnemy = 0;

	SimpleEnemyList.reserve(MAX_SIMPLE_ENEMY_TYPE);

	for (int i = 0; i < MAX_SIMPLE_ENEMY_TYPE; ++i)
	{
		SimpleEnemyList.emplace_back();
		SimpleEnemyList.back().GetPawn().AttachController(InControllerContainer.CreateAIController());
		SimpleEnemyList.back().GetPawn().SetSpeed(64.f);
	}

	InGameContext.MessageQueue.Subscribe<HitscanShotMsg>([this](auto & Msg) { OnHitscanMsg(Msg); }, Subscriptions);
}

//------------------------------------------------------------------

void CEnemyManager::SetTexture(SS::CTexture& InTexture)
{
	SimpleEnemyTexture = InTexture;
}

//------------------------------------------------------------------

void CEnemyManager::Update(float InDT)
{
	TimeUntilNextSpawn -= InDT;

	if (TimeUntilNextSpawn <= 0.f)
	{
		SpawnEnemy();
	}

	for (CEnemy* ActiveEnemyPawn : ActiveEnemies)
	{
		ActiveEnemyPawn->Update(GameContext);
	}
}

//------------------------------------------------------------------

void CEnemyManager::Render(SpelSylt::CRenderQueue& aRenderQueue)
{
	SS::CSprite Sprite;
	Sprite.SetTextureAsset(SimpleEnemyTexture.Get());

	for (CEnemy* ActiveEnemyPawn : ActiveEnemies)
	{
		Sprite.setPosition(ActiveEnemyPawn->GetPawn().GetPosition());
		aRenderQueue.Enqueue(ERenderLayer::Game, SS::SSpriteRenderCommand(Sprite));
	}
}

//------------------------------------------------------------------

void CEnemyManager::SpawnEnemy()
{
	TimeUntilNextSpawn = TimeBetweenSpawns;

	CEnemy& NextEnemy = SimpleEnemyList[NextSimpleEnemy];
	NextSimpleEnemy++;
	NextSimpleEnemy %= MAX_SIMPLE_ENEMY_TYPE;

	int RandomVal = rand() % 8;

	sf::Vector2f PositionToSpawn = { 0.f, 0.f };

	switch (RandomVal)
	{
	case 0:
		PositionToSpawn = POS_TOP_LEFT;
		break;
	case 1:
		PositionToSpawn = POS_TOP_CENTER;
		break;
	case 2:
		PositionToSpawn = POS_TOP_RIGHT;
		break;
	case 3:
		PositionToSpawn = POS_CENTER_RIGHT;
		break;
	case 4:
		PositionToSpawn = POS_BOT_RIGHT;
		break;
	case 5:
		PositionToSpawn = POS_BOT_CENTER;
		break;
	case 6:
		PositionToSpawn = POS_BOT_LEFT;
		break;
	case 7:
		PositionToSpawn = POS_CENTER_LEFT;
	default:
		break;
	}

	NextEnemy.GetPawn().SetPositon(PositionToSpawn); //Todo: Should be random

	ActiveEnemies.push_back(&NextEnemy);
}

//------------------------------------------------------------------

void CEnemyManager::KillEnemies(std::vector<int>& InEnemiesMarkedForKill)
{
	std::sort(InEnemiesMarkedForKill.begin(), InEnemiesMarkedForKill.end());

	int ErasedCount = 0;

	for (int IndexToErase : InEnemiesMarkedForKill)
	{
		IndexToErase -= ErasedCount;
		CAnimationSequencer::PlayAnimationAtPosition("Graphics/Animations/splatter.anmbndl", ActiveEnemies[IndexToErase]->GetPawn().GetPosition());
		ActiveEnemies.erase(ActiveEnemies.begin() + IndexToErase);
		ErasedCount++;
	}
}

//------------------------------------------------------------------

void CEnemyManager::OnHitscanMsg(const HitscanShotMsg& InMsg)
{
	std::vector<int> EnemiesToKill;
	EnemiesToKill.reserve(MAX_SIMPLE_ENEMY_TYPE);

	const sf::Vector2f& LineStart = InMsg.Param.first;
	const sf::Vector2f& LineEnd = InMsg.Param.second;

	CPointCollider LineStartCollider;
	LineStartCollider.setPosition(LineStart);
	CPointCollider LineEndCollider;
	LineEndCollider.setPosition(LineEnd);

	for (int i = 0; i < ActiveEnemies.size(); ++i)
	{
		CEnemy* Enemy = ActiveEnemies[i];

		CCircleCollider EnemyCollider;
		EnemyCollider.SetRadius(32.f);
		EnemyCollider.setPosition(Enemy->GetPawn().GetPosition());

		if (LineStartCollider.IsColliding(EnemyCollider) || LineEndCollider.IsColliding(EnemyCollider))
		{
			EnemiesToKill.push_back(i);
			continue;
		}

		float LineLength = Math::Length(LineStart - LineEnd);
		float Dot = ((EnemyCollider.getPosition().x - LineStart.x) * (LineEnd.x - LineStart.x)) + ((EnemyCollider.getPosition().y - LineStart.y) * (LineEnd.y - LineStart.y));
		Dot /= (LineLength * LineLength);

		sf::Vector2f ClosestPoint = LineStart + (Dot * (LineEnd - LineStart));

		//Line vs point collision
		float Tolerance = 0.1f;
		float StartToClosestPoint = Math::Length(LineStart - ClosestPoint);
		float EndToClosestPoint = Math::Length(LineEnd - ClosestPoint);

		if (StartToClosestPoint + EndToClosestPoint >= LineLength - Tolerance
			&& StartToClosestPoint + EndToClosestPoint <= LineLength + Tolerance)
		{
			if(Math::Length(ClosestPoint - EnemyCollider.getPosition()) < 32.f)
			{
				EnemiesToKill.push_back(i);
			}
		}
		else
		{
			continue;
		}
	}

	KillEnemies(EnemiesToKill);
}

//------------------------------------------------------------------