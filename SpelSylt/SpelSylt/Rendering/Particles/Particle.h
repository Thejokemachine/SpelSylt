#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

#include "SpelSylt/Math/Random.h"

namespace SpelSylt
{
	class CRenderQueue;
	class CSprite;

	struct SParticleEmitterDesc;

	class CParticle
	{
	public:
		CParticle();
		void Spawn(const Math::FSeed InSeed, const sf::Vector2f InPosition);

		bool IsActive() const;

		void Tick(float InDT, const SParticleEmitterDesc& InSettings);
		void Render(CRenderQueue& InRenderQueue, CSprite& InSprite, const SParticleEmitterDesc& InSettings);
	private:
		float TotalLifetime;
		float InterpolationValue;
		Math::FSeed ParticleSeed;
		sf::Vector2f Position;
		bool Active : 1;
	};
}

namespace SS = SpelSylt;