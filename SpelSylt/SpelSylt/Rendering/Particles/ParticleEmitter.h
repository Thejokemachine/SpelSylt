#pragma once

#include "SpelSylt/Rendering/Sprite/Sprite.h"

#include "SpelSylt/Math/Random.h"

namespace SpelSylt
{
	class CParticle;
	class CRenderQueue;

	struct SParticleEmitterDesc
	{
		sf::Vector2f StartVelocityMax;
		sf::Vector2f StartVelocityMin;
		sf::Vector2f EndVelocityMax;
		sf::Vector2f EndVelocityMin;
		sf::Vector2f Spread;
		sf::Color StartColor;
		sf::Color EndColor;
		float MinLifetime;
		float MaxLifetime;
		float MinStartScale;
		float MaxStartScale;
		float MinEndScale;
		float MaxEndScale;
		float TimeBetweenParticleSpawn;
		CSprite ParticleSprite;
	};

	class CParticleEmitter
	{
	public:
		CParticleEmitter();
		~CParticleEmitter();

		void CreateFromDesc(const SParticleEmitterDesc& InDesc);

		void SetPosition(const sf::Vector2f& InPos);

		void Tick(float InDT);
		void Render(CRenderQueue& InRenderQueue);
	private:
		const short MaxParticles = 128;

		float TimeToNextParticle;

		SParticleEmitterDesc Settings;

		Math::FSeed Seed;

		sf::Vector2f Position;
		CParticle* Particles;
		CSprite ParticleSprite;
		short NextParticle;
	};
}

namespace SS = SpelSylt;