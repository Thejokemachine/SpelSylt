#include "GameJamGame/Gameplay/Controller/InputController.h"

#include <SpelSylt/Math/CommonMath.h>
#include <SpelSylt/Utility/Input/InputEventGetter.h>

#include <SpelSylt/Messaging/MessageQueue.h>
#include "GameJamGame/Core/GameMessages.h"

//------------------------------------------------------------------

using namespace tree;

//------------------------------------------------------------------

CInputController::CInputController(const SS::IInputEventGetter& InInputGetter, SpelSylt::CMessageQueue& InMessageQueue)
	: InputGetter(InInputGetter)
	, MessageQueue(InMessageQueue)
	, CurrentDirection(0.f, 0.f)
{
}

//------------------------------------------------------------------

void CInputController::Update()
{
	CurrentDirection.x = 0.f;
	CurrentDirection.y = 0.f;

	if (InputGetter.IsKeyDown(EKeyCode::Up) || InputGetter.IsKeyDown(EKeyCode::W))
	{
		CurrentDirection.y -= 1;
	}
	if (InputGetter.IsKeyDown(EKeyCode::Down) || InputGetter.IsKeyDown(EKeyCode::S))
	{
		CurrentDirection.y += 1;
	}
	if (InputGetter.IsKeyDown(EKeyCode::Right) || InputGetter.IsKeyDown(EKeyCode::D))
	{
		CurrentDirection.x += 1;
	}
	if(InputGetter.IsKeyDown(EKeyCode::Left) || InputGetter.IsKeyDown(EKeyCode::A))
	{
		CurrentDirection.x -= 1;
	}
	if (InputGetter.IsKeyPressed(EKeyCode::Space))
	{
		MessageQueue.DispatchEvent<InteractMsg>();
	}
	if (InputGetter.IsKeyDown(EKeyCode::MouseLeft))
	{
		MessageQueue.DispatchEvent<FireWeaponMsg>(InputGetter.GetMousePosFloat());
	}
	if (InputGetter.IsKeyDown(EKeyCode::One))
	{
		MessageQueue.DispatchEvent<SwitchWeaponMsg>(0);
	}
	if (InputGetter.IsKeyDown(EKeyCode::Two))
	{
		MessageQueue.DispatchEvent<SwitchWeaponMsg>(1);
	}
	if (InputGetter.IsKeyDown(EKeyCode::Three))
	{
		MessageQueue.DispatchEvent<SwitchWeaponMsg>(2);
	}

	if (Math::Length2(CurrentDirection) > 1.f)
	{
		Math::Normalize(CurrentDirection);
	}
}

//------------------------------------------------------------------

const sf::Vector2f& tree::CInputController::GetDirection() const
{
	return CurrentDirection;
}

//------------------------------------------------------------------
