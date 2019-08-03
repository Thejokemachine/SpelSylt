#pragma once

#include "GameJamGame/Core/System.h"
#include "GameJamGame/Gameplay/Pawn.h"

#include <SpelSylt/Rendering/Sprite/Texture.h>

#include <vector>

#define MAX_SIMPLE_ENEMY_TYPE 32

namespace tree
{
	class CControllerContainer;

	class CEnemySpawner
		: public ISystem
	{
	public:	
		CEnemySpawner(CControllerContainer& InControllerContainer);

		void SetTexture(SS::CTexture& InTexture);

		void Update(float InDT) override;
		void Render(SpelSylt::CRenderQueue& aRenderQueue) override;
	private:
		void SpawnEnemy();

		SS::CTexture SimpleEnemyTexture;

		float TimeBetweenSpawns;
		float TimeUntilNextSpawn;
		size_t NextSimpleEnemy;
		std::vector<CPawn*> ActiveEnemies;
		std::vector<CPawn> SimpleEnemyList;
	};
}