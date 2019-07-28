#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/State/State.h"

#include "SpelSylt/State/StateStack.h"

#include <SFML/Graphics/RenderTarget.hpp>

using namespace SpelSylt;

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
	myShouldPop = true;
	return false;
}

void CState::PopAll()
{
	myShouldPop = true;
}

void SpelSylt::CState::PopAndPushNew(std::shared_ptr<CState> aNewState)
{
	myShouldPop = true;
	myOwner->Push(aNewState);
}

void CState::Push(std::shared_ptr<CState> aNewState)
{
	myOwner->Push(aNewState);
}
