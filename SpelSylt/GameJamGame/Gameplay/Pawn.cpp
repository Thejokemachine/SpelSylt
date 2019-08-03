#include "GameJamGame/Gameplay/Pawn.h"

#include "GameJamGame/Gameplay/Controller/ControllerInterface.h"

#include <SpelSylt/Debugging/Logging/DebugLogger.h>

//------------------------------------------------------------------

using namespace tree;

//------------------------------------------------------------------

CPawn::CPawn()
	: Speed(0.f)
	, Controller(nullptr)
	, Position(0.f, 0.f)
{
}

//------------------------------------------------------------------

void CPawn::SetSpeed(float InSpeed)
{
	Speed = InSpeed;
}

//------------------------------------------------------------------

void CPawn::AttachController(const IController& InController)
{
	Controller = &InController;
	Controller->RegisterPawn(*this);
}

//------------------------------------------------------------------

void CPawn::Tick(float InDT)
{
	if (!Controller)
	{
		LOG_WARNING(CPawn, "Pawn was ticked with unset controller. Ensure you call AttachController to Pawns!");
		return;
	}

	sf::Vector2f Direction = Controller->GetDirection();
	Position = Position + Direction * Speed * InDT;
}

//------------------------------------------------------------------

void tree::CPawn::SetPositon(const sf::Vector2f& InPosition)
{
	Position = InPosition;
}

//------------------------------------------------------------------

const sf::Vector2f& CPawn::GetPosition() const
{
	return Position;
}

//------------------------------------------------------------------