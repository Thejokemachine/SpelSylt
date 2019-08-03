#pragma once

#define MAX_INPUT_CONTROLLERS 2
#define TOTAL_CONTROLLER_COUNT MAX_INPUT_CONTROLLERS //Add all others here

#include "GameJamGame/Gameplay/Controller/InputController.h"

#include <vector>

namespace SpelSylt
{
	class IInputEventGetter;
	class CMessageQueue;
}

namespace tree
{
	class CInputController;

	class CControllerContainer
	{
	public:
		CControllerContainer();
		CInputController& CreateInputController(const SpelSylt::IInputEventGetter& InInputHandler, SpelSylt::CMessageQueue& InMessageQueue);
		void Update();
	private:
		std::vector<IController*> AllControllers;
		std::vector<CInputController> InputControllers;
	};
}