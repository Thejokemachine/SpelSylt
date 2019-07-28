#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/UI/Base/UILayout.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SpelSylt/UI/Button.h"
#include "SpelSylt/UI/Label.h"
#include "SpelSylt/tinyxml2.h"
#include "SpelSylt/Utility/Input/InputEventGetter.h"
#include "SpelSylt/UI/UIUtilities.h"
#include "SpelSylt/Math/CommonMath.h"
#include "SpelSylt/XMLUtilities.h"

#include "SpelSylt/Contexts/GameContext.h"

using namespace tinyxml2;
using namespace UI;
using namespace SpelSylt;

UILayout::UILayout(float aWidth, float aHeight, const std::string& aLayoutXML, SpelSylt::CAssetManager& aAssetManager)
	: myAssetManager(aAssetManager)
{
	bool loaded = false;
	while (!loaded)
	{
		myDocument.LoadFile(aLayoutXML.c_str());
		loaded = !myDocument.Error();
	}
	if (auto root = myDocument.FirstChildElement("layout"))
	{
		myRootPanel = std::make_unique<Panel>(*this, nullptr, "root", 0.f, 0.f, aWidth, aHeight, DockFlag::None, *root);
		addChildren(*myRootPanel, root);
	}

	Resize((int)aWidth, (int)aHeight);
}

void UILayout::Update(SGameContext& InGameContext)
{
	IInputEventGetter* aInputManager = &InGameContext.Input;

	sf::Vector2f mPos = aInputManager->GetMousePosFloat();

	myRootPanel->ForEachChild([mPos, aInputManager](Panel& panel) {
		if (aInputManager && aInputManager->IsKeyPressed(EKeyCode::MouseLeft))
		{
			if (panel.contains(mPos))
			{
				if (auto btn = dynamic_cast<Button*>(&panel))
				{
					if (btn->myOnPressed)
						btn->myOnPressed(*btn);
				}
			}
		}
		if (panel.myIsDirty)
			panel.Layout();
	});
}

void UILayout::Render(sf::RenderTarget & aRenderTarget)
{
	aRenderTarget.draw(*myRootPanel, sf::BlendAlpha);

	aRenderTarget.draw(myDrawer);
	myDrawer.clear();
}

void UILayout::Resize(int aWidth, int aHeight)
{
	LOG_VERBOSE(UI, "Resized window: width: %i height: %i", aWidth, aHeight);
	myRootPanel->SetBounds(0.f, 0.f, static_cast<float>(aWidth), static_cast<float>(aHeight));
}

Panel * UILayout::GetPanel(const std::string & aName)
{
	return myRootPanel->GetPanel(aName);
}

Button * UILayout::GetButton(const std::string & aName)
{
	return dynamic_cast<Button*>(GetPanel(aName));
}

Label * UI::UILayout::GetLabel(const std::string & aName)
{
	return dynamic_cast<Label*>(GetPanel(aName));
}

float UI::UILayout::GetWidth() const
{
	return myRootPanel->GetWidth();
}

float UI::UILayout::GetHeight() const
{
	return myRootPanel->GetHeight();
}

void UILayout::addChildren(Panel& aParent, XMLElement* aElement)
{
	auto child = aElement->FirstChildElement();
	while (child)
	{
		std::string val = child->Value();
		std::shared_ptr<Panel> panel = nullptr;

		if (val == "panel")
		{
			panel = std::make_shared<Panel>(*this, &aParent, *child);
		}
		else if (val == "button")
		{
			panel = std::make_shared<Button>(*this, &aParent, *child);
		}
		else if (val == "text")
		{
			panel = std::make_shared<Label>(*this, &aParent, *child);
		}

		if (panel)
		{
			addChildren(*panel, child);
			aParent.AddPanel(panel);
		}

		child = child->NextSiblingElement();
	}
}

float UI::UILayout::evaluateExpression(const std::string & aAttributeBlock)
{
	return 0.0f;
}
