#pragma once

#include "SpelSylt/Rendering/Sprite/Sprite.h"

namespace SpelSylt
{
	class CParticle;
	class CRenderQueue;

	struct SParticleEmitterDesc
	{
		sf::Vector2f VelocityMax;
		sf::Vector2f VelocityMin;
		sf::Vector2f AccelerationMax;
		sf::Vector2f AccelerationMin;
		sf::Vector2f Spread;
		sf::Color StartColor;
		sf::Color EndColor;
		float MinLifetime;
		float MaxLifetime;
		float MinStartScale;
		float MaxStartScale;
		float MinEndScale;
		float MaxEndScale;
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

		float TimeBetweenParticles;
		float TimeToNextParticle;

		SParticleEmitterDesc Settings;

		sf::Vector2f Position;
		CParticle* Particles;
		CSprite ParticleSprite;
		short NextParticle;
	};
}

namespace SS = SpelSylt;