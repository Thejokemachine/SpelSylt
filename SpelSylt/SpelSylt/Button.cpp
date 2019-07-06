#include "SpelSyltPCH.h"

#include "Button.h"

using namespace UI;

UI::Button::Button(UI::UILayout & aLayout, const Panel * aParent, const std::string & aName, float x, float y, float aWidth, float aHeight, unsigned char aDockFlags, tinyxml2::XMLElement& aElement) :
	Panel(aLayout, aParent, aName, x, y, aWidth, aHeight, aDockFlags, aElement)
{
}

void Button::SetCallback(std::function<void(Button&button)> aOnPressed)
{
	myOnPressed = aOnPressed;
}
