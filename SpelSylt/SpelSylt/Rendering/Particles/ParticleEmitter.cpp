#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/Rendering/Particles/ParticleEmitter.h"

#include "SpelSylt/Rendering/Particles/Particle.h"

#include "SpelSylt/Math/CommonMath.h"

//------------------------------------------------------------------

using namespace SpelSylt;

//------------------------------------------------------------------

CParticleEmitter::CParticleEmitter()
	: TimeBetweenParticles(0.02f)
	, TimeToNextParticle(0.f)
	, Particles(nullptr)
	, ParticleSprite()
	, NextParticle(0)
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
		TimeToNextParticle = TimeBetweenParticles;

		SParticleDesc TestDesc;
		TestDesc.Position.x = Math::RandomInRange(Position.x - Settings.Spread.x, Position.x + Settings.Spread.x);
		TestDesc.Position.y = Math::RandomInRange(Position.y - Settings.Spread.y, Position.y + Settings.Spread.y);

		TestDesc.Velocity.x = Math::RandomInRange(Settings.VelocityMin.x, Settings.VelocityMax.x);
		TestDesc.Velocity.y = Math::RandomInRange(Settings.VelocityMin.y, Settings.VelocityMax.y);

		TestDesc.Acceleration.x = Math::RandomInRange(Settings.AccelerationMin.x, Settings.AccelerationMax.x);
		TestDesc.Acceleration.y = Math::RandomInRange(Settings.AccelerationMin.y, Settings.AccelerationMax.y);

		TestDesc.AllowedLifetime = Math::RandomInRange(Settings.MinLifetime, Settings.MaxLifetime);

		TestDesc.StartScale = Math::RandomInRange(Settings.MinStartScale, Settings.MaxStartScale);
		TestDesc.EndScale = Math::RandomInRange(Settings.MinEndScale, Settings.MaxEndScale);

		TestDesc.StartColor = Settings.StartColor;
		TestDesc.EndColor = Settings.EndColor;

		Particles[NextParticle].Spawn(TestDesc);
		NextParticle++;
		NextParticle %= MaxParticles;
	}

	for (short i = 0; i < MaxParticles; ++i)
	{
		if (!Particles[i].IsActive())
		{
			continue;
		}

		Particles[i].Tick(InDT);
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

		Particles[i].Render(InRenderQueue, Settings.ParticleSprite);
	}
}

//------------------------------------------------------------------