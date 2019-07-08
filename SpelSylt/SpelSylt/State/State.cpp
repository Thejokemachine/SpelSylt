#include "SpelSyltPCH.h"

#include "State/State.h"

#include "State/StateStack.h"

CState::CState()
	: myOwner(nullptr)
{
	SetStateFlags(static_cast<int>(StateFlags::NONE));
}

CState::~CState()
{
}

void CState::SetOwner(CStateStack * aOwner)
{
	myOwner = aOwner;
}

void CState::SetStateFlags(int aStateFlags)
{
	SetStateFlags(static_cast<StateFlags>(aStateFlags));
}

void CState::SetStateFlags(CState::StateFlags aStateFlags)
{
	myStateFlags = aStateFlags;
}

bool CState::Pop()
{
	return myOwner->Pop();
}

void CState::PopAll()
{
	myOwner->PopAll();
}

/*void CState::Push(CState * aNewState)
{
	myOwner->Push(aNewState);
}*/
