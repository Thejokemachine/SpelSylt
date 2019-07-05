#include "SpelSyltPCH.h"
#include "Text.h"
#include "tinyxml2.h"
#include "XMLUtilities.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "UIUtilities.h"

UI::Text::Text(const Panel* aParent, const std::string & aName, float x, float y, float aWidth, float aHeight, unsigned char aDockFlags, tinyxml2::XMLElement & aElement) :
	Panel(aParent, aName, x, y, aWidth, aHeight, aDockFlags)
{
	std::string text = "";
	XMLUtilities::QueryAttribute(aElement, "string", text);

	myFont.loadFromFile("Graphics/Fonts/default.ttf");
	myText.setFont(myFont);
	myText.setString(text);

	myText.setPosition(aParent->GetX(), aParent->GetY());

	std::string color;
	XMLUtilities::QueryAttribute(aElement, "text_color", color);

	myText.setFillColor(UIUtilities::EvaluateColor(color));
}

void UI::Text::onDraw(sf::RenderTarget& aTarget) const
{
	aTarget.draw(myText);
}
