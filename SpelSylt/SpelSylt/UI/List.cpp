#include "SpelSylt/SpelSyltPCH.h"
#include "List.h"
#include "SpelSylt/XMLUtilities.h"
#include "SpelSylt/Utility/Input/InputEventGetter.h"
#include "SpelSylt/UI/Base/UILayout.h"
#include "SpelSylt/Math/CommonMath.h"

#include <SFML/Graphics/RenderTarget.hpp>

using namespace tinyxml2;

UI::List::List(UILayout& aLayout, const Panel* aParent, tinyxml2::XMLElement& aElement) :
	Panel(aLayout, aParent, aElement)
{
	myIsScissor = true;

	XMLElement* listItem = aElement.FirstChildElement("list_item");
	while (listItem)
	{
		std::string name;
		XMLUtilities::QueryAttribute(*listItem, "name", name);

		myItemTemplates[name] = listItem;

		listItem = listItem->NextSiblingElement("list_item");
	}

	XMLUtilities::QueryAttribute(aElement, "item_margin", myMargin);
}

UI::Panel* UI::List::AddItem(const std::string& aItemTemplateName)
{
	if (myItemTemplates.find(aItemTemplateName) != myItemTemplates.end())
	{
		auto item = std::make_shared<Panel>(myLayout, this, *myItemTemplates.at(aItemTemplateName));
		myItems.emplace_back(item);

		myMaxScroll += item->GetHeight() + myMargin;

		return item.get();
	}

	return nullptr;
}

void UI::List::onUpdate(const float dt)
{
	for (int i = 0; i < myItems.size(); ++i)
	{
		auto& item = myItems[i];
		item->SetBounds(item->GetX(), myScroll+GetY()+(item->GetHeight()+myMargin) * i, item->GetWidth(), item->GetHeight());
		item->Update(dt);
	}
}

void UI::List::onHover()
{
	auto& input = myLayout.GetInputManager();
	myScroll -= 10*input.GetScrollWheelDelta();
	myScroll = Math::Clamp(myScroll, 0.f, myMaxScroll);
}

void UI::List::onLayout()
{
	for (auto& item : myItems)
	{
		item->Layout();
	}
}

void UI::List::onDraw(sf::RenderTarget & aTarget) const
{
	for (auto& item : myItems)
	{
		item->draw(aTarget, sf::RenderStates::Default);
	}
}
