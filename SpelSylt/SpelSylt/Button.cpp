#include "Button.h"

void Button::SetCallback(std::function<void(Button&button)> aOnPressed)
{
	myOnPressed = aOnPressed;
}
