#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/UI/Base/UILayout.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SpelSylt/UI/Button.h"
#include "SpelSylt/UI/Label.h"
#include "SpelSylt/UI/List.h"
#include "SpelSylt/tinyxml2.h"
#include "SpelSylt/Utility/Input/InputEventGetter.h"
#include "SpelSylt/UI/UIUtilities.h"
#include "SpelSylt/Math/CommonMath.h"
#include "SpelSylt/XMLUtilities.h"
#include "SpelSylt/Utility/Time/Time.h"

#include "SpelSylt/Contexts/GameContext.h"

using namespace tinyxml2;
using namespace UI;
using namespace SpelSylt;

UILayout::UILayout(float aWidth, float aHeight, const std::string& aLayoutXML, SpelSylt::CAssetManager& aAssetManager, SpelSylt::IInputEventGetter& aInputManager) :
	myAssetManager(aAssetManager),
	myInputManager(aInputManager)
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
	}

	Resize((int)aWidth, (int)aHeight);
}

void UILayout::Update(SGameContext& InGameContext)
{
	IInputEventGetter* aInputManager = &InGameContext.Input;

	sf::Vector2f mPos = aInputManager->GetMousePosFloat();

	myRootPanel->ForEachChild([&mPos, &aInputManager, &InGameContext](Panel& panel) {
		panel.Update(InGameContext.Time.GetDeltaTime());
		if (panel.contains(mPos))
		{
			panel.onHover();
			if (aInputManager && aInputManager->IsKeyPressed(EKeyCode::MouseLeft))
			{
				if (auto btn = dynamic_cast<Button*>(&panel))
				{
					if (btn->myOnPressed)
						btn->myOnPressed(*btn);
				}
			}
		}
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

List * UI::UILayout::GetList(const std::string & aName)
{
	return dynamic_cast<List*>(GetPanel(aName));
}

float UI::UILayout::GetWidth() const
{
	return myRootPanel->GetWidth();
}

float UI::UILayout::GetHeight() const
{
	return myRootPanel->GetHeight();
}

float UI::UILayout::evaluateExpression(const std::string & aAttributeBlock)
{
	return 0.0f;
}
