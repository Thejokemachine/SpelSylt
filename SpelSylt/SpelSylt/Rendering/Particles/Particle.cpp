#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/Rendering/Particles/Particle.h"

#include "SpelSylt/Rendering/RenderCommand.h"
#include "SpelSylt/Rendering/RenderQueue.h"
#include "SpelSylt/Rendering/Sprite/Sprite.h"

#include "SpelSylt/Math/CommonMath.h"

//TODO: Move struct somewhere nicer :D
#include "SpelSylt/Rendering/Particles/ParticleEmitter.h"




//------------------------------------------------------------------

using namespace SpelSylt;

//------------------------------------------------------------------

CParticle::CParticle()
	: TotalLifetime(0.f)
	, Active(false)
{
}

//------------------------------------------------------------------

void CParticle::Spawn(const Math::FSeed InSeed, const sf::Vector2f InPosition)
{
	ParticleSeed = InSeed;
	Position = InPosition;
	TotalLifetime = 0.f;
	Active = true;
}

//------------------------------------------------------------------

bool CParticle::IsActive() const
{
	return Active;
}

//------------------------------------------------------------------

void CParticle::Tick(float InDT, const SParticleEmitterDesc& InSettings)
{
	Math::CRandom Rand(ParticleSeed);

	TotalLifetime += InDT;
	const float AllowedLifetime = Rand.RandFloatInRange(InSettings.MinLifetime, InSettings.MaxLifetime);
	InterpolationValue = TotalLifetime / AllowedLifetime;

	if (TotalLifetime >= AllowedLifetime)
	{
		Active = false;
	}

	const sf::Vector2f StartVelocity = Rand.RandVec2InRange(InSettings.StartVelocityMin, InSettings.StartVelocityMax);
	const sf::Vector2f EndVelocity = Rand.RandVec2InRange(InSettings.EndVelocityMin, InSettings.EndVelocityMax);
	const sf::Vector2f CurrentVelocity = Math::Lerp(StartVelocity, EndVelocity, InterpolationValue);
	Position += CurrentVelocity * InDT;
}

//------------------------------------------------------------------

void CParticle::Render(CRenderQueue& InRenderQueue, CSprite& InSprite, const SParticleEmitterDesc& InSettings)
{
	sf::Color Color = Math::LerpColor(InSettings.StartColor, InSettings.EndColor, InterpolationValue);

	Math::CRandom Rand(ParticleSeed);
	const float StartScale = Rand.RandFloatInRange(InSettings.MinStartScale, InSettings.MaxStartScale);
	const float EndScale = Rand.RandFloatInRange(InSettings.MinEndScale, InSettings.MaxEndScale);
	const float Scale = Math::Lerp(StartScale, EndScale, InterpolationValue);

	InSprite.setPosition(Position);
	InSprite.setScale(Scale, Scale);
	InSprite.setColor(Color);

	InRenderQueue.Enqueue(ERenderLayer::Game, SSpriteRenderCommand(InSprite));
}

//------------------------------------------------------------------