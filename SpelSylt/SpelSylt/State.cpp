#include "State.h"

#include "StateStack.h"

CState::CState()
{
}

CState::~CState()
{
}

void CState::SetOwner(CStateStack * aOwner)
{
	myOwner = aOwner;
}

bool CState::Pop()
{
	return myOwner->Pop();
}

void CState::PopAll()
{
	myOwner->PopAll();
}

void CState::Push(CState * aNewState)
{
	myOwner->Push(aNewState);
}
