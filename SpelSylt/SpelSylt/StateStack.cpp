#include "SpelSyltPCH.h"

#include "StateStack.h"

#include "State.h"


CStateStack::CStateStack()
	: myStates()
	, myCurrentStateIndex(0)
{
}


CStateStack::~CStateStack()
{
}

void CStateStack::Update(SGameContext& InGameContext)
{
	if (myStates.size() > 0)
	{
		myStates[myCurrentStateIndex]->Update(InGameContext);
	}
}

void CStateStack::Render(SRenderingContext& InRenderingContext)
{
	if (myStates.size() > 0)
	{
		myStates[myCurrentStateIndex]->Render(InRenderingContext);
	}
}

void CStateStack::Push(CState * aNewState)
{
	myCurrentStateIndex = static_cast<short>(myStates.size());
	myStates.push_back(aNewState);
	aNewState->SetOwner(this);
	aNewState->Init();
}

bool CStateStack::Pop()
{
	if (myStates.size() > 0)
	{
		delete myStates[myCurrentStateIndex];
		myStates[myCurrentStateIndex] = nullptr;

		myStates.pop_back();
		myCurrentStateIndex--;
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
