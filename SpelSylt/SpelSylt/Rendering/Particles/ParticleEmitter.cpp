#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/Rendering/Particles/ParticleEmitter.h"

#include "SpelSylt/Rendering/Particles/Particle.h"

#include "SpelSylt/Math/CommonMath.h"

//------------------------------------------------------------------

using namespace SpelSylt;

//------------------------------------------------------------------

CParticleEmitter::CParticleEmitter()
	: TimeToNextParticle(0.f)
	, Particles(nullptr)
	, ParticleSprite()
	, NextParticle(0)
	, Seed(1)
{
	Particles = new CParticle[MaxParticles];
}

//------------------------------------------------------------------

CParticleEmitter::~CParticleEmitter()
{
	delete[MaxParticles] Particles;
}

//------------------------------------------------------------------

void CParticleEmitter::CreateFromDesc(const SParticleEmitterDesc& InDesc)
{
	Settings = InDesc;
}

//------------------------------------------------------------------

void CParticleEmitter::SetPosition(const sf::Vector2f& InPos)
{
	Position = InPos;
}

//------------------------------------------------------------------

void CParticleEmitter::Tick(float InDT)
{
	TimeToNextParticle -= InDT;
	
	if (TimeToNextParticle <= 0.f)
	{
		TimeToNextParticle = Settings.TimeBetweenParticleSpawn;

		Particles[NextParticle].Spawn(Seed++, Position);
		NextParticle++;
		NextParticle %= MaxParticles;
	}

	for (short i = 0; i < MaxParticles; ++i)
	{
		if (!Particles[i].IsActive())
		{
			continue;
		}

		Particles[i].Tick(InDT, Settings);
	}
}

//------------------------------------------------------------------

void CParticleEmitter::Render(CRenderQueue& InRenderQueue)
{
	for (short i = 0; i < MaxParticles; ++i)
	{
		if (!Particles[i].IsActive())
		{
			continue;
		}

		Particles[i].Render(InRenderQueue, Settings.ParticleSprite, Settings);
	}
}

//------------------------------------------------------------------