#include "SpelSyltPCH.h"

#include "Button.h"

using namespace UI;

void Button::SetCallback(std::function<void(Button&button)> aOnPressed)
{
	myOnPressed = aOnPressed;
}
