#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/Rendering/Particles/Particle.h"

#include "SpelSylt/Rendering/RenderCommand.h"
#include "SpelSylt/Rendering/RenderQueue.h"
#include "SpelSylt/Rendering/Sprite/Sprite.h"

#include "SpelSylt/Math/CommonMath.h"


//------------------------------------------------------------------

using namespace SpelSylt;

//------------------------------------------------------------------

CParticle::CParticle()
	: Data()
	, TotalLifetime(0.f)
	, Active(false)
{
}

//------------------------------------------------------------------

void CParticle::Spawn(const SParticleDesc& InDesc)
{
	Data = InDesc;
	TotalLifetime = 0.f;
	Active = true;
}

//------------------------------------------------------------------

bool CParticle::IsActive() const
{
	return Active;
}

//------------------------------------------------------------------

void CParticle::Tick(float InDT)
{
	TotalLifetime += InDT;
	if (TotalLifetime >= Data.AllowedLifetime)
	{
		Active = false;
	}

	Data.Velocity += Data.Acceleration * InDT;
	Data.Position += Data.Velocity * InDT;
}

//------------------------------------------------------------------

void CParticle::Render(CRenderQueue& InRenderQueue, CSprite& InSprite)
{
	InSprite.setPosition(Data.Position);
	float Scale = Math::Lerp(Data.StartScale, Data.EndScale, TotalLifetime / Data.AllowedLifetime);
	InSprite.setScale(Scale, Scale);
	sf::Color Color;
	Color = Math::LerpColor(Data.StartColor, Data.EndColor, TotalLifetime / Data.AllowedLifetime);
	InSprite.setColor(Color);
	InRenderQueue.Enqueue(ERenderLayer::Game, SSpriteRenderCommand(InSprite));
}

//------------------------------------------------------------------