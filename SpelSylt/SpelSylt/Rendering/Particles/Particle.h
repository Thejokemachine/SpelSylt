#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

namespace SpelSylt
{
	class CRenderQueue;
	class CSprite;

	struct SParticleDesc
	{
		sf::Vector2f Position;
		sf::Vector2f Velocity;
		sf::Vector2f Acceleration;
		sf::Color StartColor;
		sf::Color EndColor;
		float StartScale;
		float EndScale;
		float AllowedLifetime;
	};

	class CParticle
	{
	public:
		CParticle();
		void Spawn(const SParticleDesc& InDesc);

		bool IsActive() const;

		void Tick(float InDT);
		void Render(CRenderQueue& InRenderQueue, CSprite& InSprite);
	private:
		SParticleDesc Data;
		float TotalLifetime;

		bool Active : 1;
	};
}

namespace SS = SpelSylt;