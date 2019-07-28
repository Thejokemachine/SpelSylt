#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/State/StateStack.h"

#include "SpelSylt/State/State.h"

#include <assert.h>

using namespace SpelSylt;

CStateStack::CStateStack()
	: myStates()
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

		if (state.myShouldPop)
		{
			assert(i == myStates.size() - 1); // Only allowed to pop the highest layer!
			Pop();
			break;
		}

		if (!(state.GetStateFlags() & CState::StateFlags::UPDATE_BELOW))
			break;
	}

	for (int i = 0; i < myStatesToPush.size(); ++i)
	{
		auto state = myStatesToPush[i];
		state->Init(InGameContext);
		myStates.push_back(state);
	}
	myStatesToPush.clear();
}

void CStateStack::Render(sf::RenderTarget& InTarget)
{
	int index = (int)myStates.size() - 1;

	std::function<void()> func;
	func = [this, &InTarget, &index, &func]() {
		if (index < 0)
			return;

		CState& state = *myStates[index--];
		if (state.GetStateFlags() & CState::StateFlags::DRAW_BELOW)
			func();
		state.Render(InTarget);
	};

	func();
}

void CStateStack::Push(std::shared_ptr<CState> aNewState)
{
	aNewState->SetOwner(this);
	myStatesToPush.push_back(aNewState);
}

bool CStateStack::Pop()
{
	if (myStates.size() > 0)
	{
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

void CStateStack::PopAndPush(std::shared_ptr<CState> aNewState)
{
	Pop();
	Push(aNewState);
}

short CStateStack::Size()
{
	return static_cast<short>(myStates.size());
}
