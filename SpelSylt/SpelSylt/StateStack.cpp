#include "StateStack.h"

#include "State.h"


CStateStack::CStateStack()
{
}


CStateStack::~CStateStack()
{
}

void CStateStack::Update(float dt)
{
	if (myStates.size() > 0)
	{
		myStates[myCurrentStateIndex]->Update(dt);
	}
}

void CStateStack::Render(sf::RenderWindow * aRenderWindow)
{
	if (myStates.size() > 0)
	{
		myStates[myCurrentStateIndex]->Render(aRenderWindow);
	}
}

void CStateStack::Push(CState * aNewState)
{
	myCurrentStateIndex = myStates.size();
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
	return myStates.size();
}
