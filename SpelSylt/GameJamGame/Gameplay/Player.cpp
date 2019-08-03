#include "Player.h"
#include <SpelSylt/Math/CommonMath.h>

void tree::CPlayer::Tick(float InDT)
{
	CPawn::Tick(InDT);

	float halfWidth = 1920.f / 2.f;
	float halfHeight = 1080.f / 2.f;

	Position.x = Math::Clamp(Position.x, -halfWidth, halfWidth);
	Position.y = Math::Clamp(Position.y, -halfHeight, halfHeight);
}
