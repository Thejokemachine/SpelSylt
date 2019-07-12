#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/State/StateStack.h"

#include "SpelSylt/State/State.h"


CStateStack::CStateStack(sf::Window& aWindow)
	: myStates(), myWindow(aWindow)
{
}


CStateStack::~CStateStack()
{
}

void CStateStack::Update(SGameContext& InGameContext)
{
	for (int i = static_cast<int>(myStates.size()) - 1; i >= 0; --i)
	{
		CState& state = *myStates[i];
		state.Update(InGameContext);
		if (!(state.GetStateFlags() & CState::StateFlags::UPDATE_BELOW))
			break;
	}
}

void CStateStack::Render(SRenderingContext& InRenderingContext)
{
	for (int i = static_cast<int>(myStates.size()) - 1; i >= 0; --i)
	{
		CState& state = *myStates[i];
		state.Render(InRenderingContext);
		if (!(state.GetStateFlags() & CState::StateFlags::DRAW_BELOW))
			break;
	}
}

void CStateStack::Push(CState * aNewState, SGameContext& InGameContext, SRenderingContext& InRenderingContext)
{
	myStates.push_back(aNewState);
	aNewState->SetOwner(this);
	aNewState->Init(InGameContext, InRenderingContext);
}

bool CStateStack::Pop()
{
	if (myStates.size() > 0)
	{
		delete myStates.back();
		myStates.back() = nullptr;

		myStates.pop_back();
		return true;
	}
	return false;
}

void CStateStack::PopAll()
{
	while (myStates.size() > 0)
	{
		Pop();
	}
}

short CStateStack::Size()
{
	return static_cast<short>(myStates.size());
}
