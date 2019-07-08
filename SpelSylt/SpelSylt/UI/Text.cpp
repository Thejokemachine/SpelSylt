#include "SpelSyltPCH.h"
#include "UI/Text.h"
#include "tinyxml2.h"
#include "XMLUtilities.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "UI/UIUtilities.h"
#include "UI/Base/UILayout.h"
#include "FileHandling/Banks/FontBank.h"

UI::Text::Text(UILayout& aLayout, const Panel* aParent, const std::string & aName, float x, float y, float aWidth, float aHeight, unsigned char aDockFlags, tinyxml2::XMLElement & aElement) :
	Panel(aLayout, aParent, aName, x, y, aWidth, aHeight, aDockFlags, aElement)
{
	std::string text = "";
	XMLUtilities::QueryAttribute(aElement, "string", text);

	myText.setString(text);

	std::string color;
	XMLUtilities::QueryAttribute(aElement, "text_color", color);
	std::string align;
	XMLUtilities::QueryAttribute(aElement, "align", align);
	unsigned short flags = UIUtilities::EvaluateDockingFlags(align);
	int size = 30;
	XMLUtilities::QueryAttribute(aElement, "size", size);
	myText.setCharacterSize(size);
	std::string font = "default";
	XMLUtilities::QueryAttribute(aElement, "font", font);
	if (auto f = myLayout.GetFontBank().GetFont(font))
		myText.setFont(*f);
	
	sf::Vector2f dockOffset;
	sf::Vector2f origin = sf::Vector2f(myText.getLocalBounds().left, myText.getLocalBounds().top);
	if (flags & DockFlag::Bottom)
	{
		dockOffset.y += GetHeight();
		origin.y = myText.getLocalBounds().top + myText.getLocalBounds().height;
	}
	if (flags & DockFlag::Right)
	{
		dockOffset.x += GetWidth();
		origin.x = myText.getLocalBounds().width;
	}
	if (flags & DockFlag::Center)
	{
		dockOffset = sf::Vector2f(GetWidth()*0.5f, GetHeight()*0.5f);
		origin.x = myText.getLocalBounds().width * 0.5f;
		origin.y = myText.getLocalBounds().top + myText.getLocalBounds().height * 0.5f;
	}
	if (flags & DockFlag::HCenter)
	{
		dockOffset.x = GetWidth();
		origin.x = myText.getLocalBounds().width * 0.5f;
	}
	if (flags & DockFlag::VCenter)
	{
		dockOffset.y = GetHeight();
		origin.y = myText.getLocalBounds().top + myText.getLocalBounds().height * 0.5f;
	}

	myText.setOrigin(origin);

	myText.setPosition(GetX(), GetY());
	myText.move(dockOffset);

	myText.setFillColor(UIUtilities::EvaluateColor(color));
}

void UI::Text::onDraw(sf::RenderTarget& aTarget) const
{
	aTarget.draw(myText);
}
