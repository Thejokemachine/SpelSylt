#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/UI/Base/UILayout.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SpelSylt/UI/Button.h"
#include "SpelSylt/UI/Text.h"
#include "SpelSylt/tinyxml2.h"
#include "SpelSylt/Utility/Input/InputEventGetter.h"
#include "SpelSylt/UI/UIUtilities.h"
#include "SpelSylt/Math/CommonMath.h"
#include "SpelSylt/XMLUtilities.h"

using namespace tinyxml2;
using namespace UI;

UILayout::UILayout(float aWidth, float aHeight, CFontBank& aFontBank) :
myFontBank(aFontBank)
{
	myDocument.LoadFile("UI/Layouts/hookGame_layout.xml");
	if (auto root = myDocument.FirstChildElement("layout"))
	{
		myRootPanel = std::make_unique<Panel>(*this, nullptr, "root", 0.f, 0.f, aWidth, aHeight, DockFlag::None, *root);
		addChildren(*myRootPanel, root);
	}
}

void UILayout::Update(IInputEventGetter* aInputManager)
{
	sf::Vector2f mPos = aInputManager->GetMousePosFloat();

	if (aInputManager && aInputManager->IsKeyPressed(EKeyCode::MouseLeft))
	{
		myRootPanel->ForEachChild([mPos](Panel& panel) {
			if (panel.contains(mPos))
			{
				if (auto btn = dynamic_cast<Button*>(&panel))
				{
					if (btn->myOnPressed)
						btn->myOnPressed(*btn);
				}
			}
		});
	}
}

void UILayout::Render(sf::RenderTarget & aRenderTarget)
{
	aRenderTarget.draw(*myRootPanel, sf::BlendAlpha);

	myRootPanel->ForEachChild([this](Panel& panel){
		sf::Vector2f center;
		center.x = panel.GetX() + panel.GetWidth() * 0.5f;
		center.y = panel.GetY() + panel.GetHeight() * 0.5f;
		myDrawer.DrawRectangle(center, panel.GetWidth(), panel.GetHeight());
	});

	aRenderTarget.draw(myDrawer);
	myDrawer.clear();
}

void UILayout::Resize(int aWidth, int aHeight)
{
	LOG_VERBOSE(UI, "Resized window: width: %i height: %i", aWidth, aHeight);
	myRootPanel->Resize((float)aWidth, (float)aHeight);
}

Panel * UILayout::GetPanel(const std::string & aName)
{
	return myRootPanel->GetPanel(aName);
}

Button * UILayout::GetButton(const std::string & aName)
{
	return dynamic_cast<Button*>(GetPanel(aName));
}

void UILayout::addChildren(Panel& aParent, XMLElement* aElement)
{
	auto child = aElement->FirstChildElement();
	while (child)
	{
		std::string val = child->Value();
		std::shared_ptr<Panel> panel = nullptr;

		std::string name = "";
		float x = 0;
		float y = 0;
		float height = 0;
		float width = 0;
		std::string image = "";
		std::string dockFlagsValue = "";
		std::string colorValue = "";

		XMLUtilities::QueryAttribute(*child, "name", name);
		XMLUtilities::QueryAttribute(*child, "x", x);
		XMLUtilities::QueryAttribute(*child, "y", y);
		XMLUtilities::QueryAttribute(*child, "height", height);
		XMLUtilities::QueryAttribute(*child, "width", width);
		XMLUtilities::QueryAttribute(*child, "dock", dockFlagsValue);
		XMLUtilities::QueryAttribute(*child, "image", image);
		XMLUtilities::QueryAttribute(*child, "color", colorValue);

		unsigned char dockFlags = UIUtilities::EvaluateDockingFlags(dockFlagsValue);
		sf::Color color = UIUtilities::EvaluateColor(colorValue);

		if (val == "panel")
		{
			panel = std::make_shared<Panel>(*this, &aParent, name, x, y, width, height, dockFlags, *child);
		}
		else if (val == "button")
		{
			panel = std::make_shared<Button>(*this, &aParent, name, x, y, width, height, dockFlags, *child);
		}
		else if (val == "text")
		{
			panel = std::make_shared<Text>(*this, &aParent, name, x, y, width, height, dockFlags, *child);
		}

		if (panel)
		{
			if (!image.empty())
				panel->SetImage(image);
			panel->SetColor(color);

			addChildren(*panel, child);
		}

		aParent.AddPanel(panel);
		child = child->NextSiblingElement();
	}
}
