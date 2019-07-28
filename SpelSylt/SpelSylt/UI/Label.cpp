#include "SpelSylt/SpelSyltPCH.h"
#include "SpelSylt/UI/Label.h"
#include "SpelSylt/tinyxml2.h"
#include "SpelSylt/XMLUtilities.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SpelSylt/UI/UIUtilities.h"
#include "SpelSylt/UI/Base/UILayout.h"

#include "SpelSylt/FileHandling/Asset/AssetTypes/FontAsset.h"
#include "SpelSylt/FileHandling/Asset/AssetManager.h"

UI::Label::Label(UILayout& aLayout, const Panel* aParent, tinyxml2::XMLElement & aElement) :
	Panel(aLayout, aParent, aElement)
{
	std::string text = "";
	XMLUtilities::QueryAttribute(aElement, "string", text);

	myText.setString(text);

	std::string color;
	XMLUtilities::QueryAttribute(aElement, "text_color", color);
	std::string align;
	XMLUtilities::QueryAttribute(aElement, "align", align);
	myTextAlignFlags = UIUtilities::EvaluateDockingFlags(align);
	int size = 30;
	XMLUtilities::QueryAttribute(aElement, "size", size);
	myText.setCharacterSize(size);
	std::string font = "default";
	XMLUtilities::QueryAttribute(aElement, "font", font);
	float outlineThickness = 0.f;
	XMLUtilities::QueryAttribute(aElement, "outline_size", outlineThickness);
	std::string outlineColor;
	XMLUtilities::QueryAttribute(aElement, "outline_color", outlineColor);

	std::string FullFontPath = "Graphics/Fonts/" + font + ".ttf";
	myText.SetFontAsset(myLayout.GetFontBank().GetAsset<SS::SFontAsset>(FullFontPath.c_str(), ELoadSettings::Synchronous));

	myText.setOutlineThickness(outlineThickness);
	if (!outlineColor.empty())
		myText.setOutlineColor(UIUtilities::EvaluateColor(outlineColor));
	float spacing = 1.f;
	XMLUtilities::QueryAttribute(aElement, "spacing", spacing);
	myText.setLetterSpacing(spacing);

	onLayout();

	myText.setFillColor(UIUtilities::EvaluateColor(color));
}

void UI::Label::SetText(const std::string & aText)
{
	if (aText != myText.getString())
		setDirty();

	myText.setString(aText);
}

void UI::Label::onLayout()
{
	sf::Vector2f dockOffset;
	sf::Vector2f origin = sf::Vector2f(myText.getLocalBounds().left, myText.getLocalBounds().top);
	if (myTextAlignFlags & DockFlag::Bottom)
	{
		dockOffset.y += GetHeight();
		origin.y = myText.getLocalBounds().top + myText.getLocalBounds().height;
	}
	if (myTextAlignFlags & DockFlag::Right)
	{
		dockOffset.x += GetWidth();
		origin.x = myText.getLocalBounds().width;
	}
	if (myTextAlignFlags & DockFlag::Center)
	{
		dockOffset = sf::Vector2f(GetWidth()*0.5f, GetHeight()*0.5f);
		origin.x = myText.getLocalBounds().width * 0.5f;
		origin.y = myText.getLocalBounds().top + myText.getLocalBounds().height * 0.5f;
	}
	if (myTextAlignFlags & DockFlag::HCenter)
	{
		dockOffset.x = GetWidth();
		origin.x = myText.getLocalBounds().width * 0.5f;
	}
	if (myTextAlignFlags & DockFlag::VCenter)
	{
		dockOffset.y = GetHeight();
		origin.y = myText.getLocalBounds().top + myText.getLocalBounds().height * 0.5f;
	}

	myText.setOrigin(origin);

	myText.setPosition(GetX(), GetY());
	myText.move(dockOffset);
}

void UI::Label::onDraw(sf::RenderTarget& aTarget) const
{
	aTarget.draw(myText);
}
