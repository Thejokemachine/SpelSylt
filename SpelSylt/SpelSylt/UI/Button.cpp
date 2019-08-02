#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/UI/Button.h"

using namespace UI;

UI::Button::Button(UI::UILayout & aLayout, const Panel * aParent, tinyxml2::XMLElement& aElement) :
	Panel(aLayout, aParent, aElement)
{
}

void Button::SetCallback(std::function<void(Button&button)> aOnPressed)
{
	myOnPressed = aOnPressed;
}

void UI::Button::onHover()
{
	myHoveredColor = sf::Color(100, 100, 100, 255);
}
