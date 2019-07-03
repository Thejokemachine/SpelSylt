#include "SpelSyltPCH.h"

#include "UILayout.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "Button.h"
#include "tinyxml2.h"

#include <iostream>

using namespace tinyxml2;

UILayout::UILayout(float aWidth, float aHeight) : 
myRootPanel(nullptr, "root", 0.f, 0.f, aWidth, aHeight, DockFlag::None)
{
	auto middle = std::make_shared<Button>(&myRootPanel, "", 15.f, 15.f, aWidth * 0.1f, aHeight * 0.1f, DockFlag::Center);

	middle->SetCallback([](Button& button) {
		std::cout << "AAAAAJ" << std::endl;
	});
	myRootPanel.AddPanel(middle);

	XMLDocument layout;
	layout.LoadFile("UI/Layouts/hookGame_layout.xml");
	if (auto root = layout.FirstChildElement("layout"))
	{
		addChildren(myRootPanel, root);
	}
}

void UILayout::Update(CInputManager * aInputManager)
{
	sf::Vector2f mPos = aInputManager->GetMousePosFloat();

	if (aInputManager && aInputManager->IsKeyPressed(EKeyCode::MouseLeft))
	{
		myRootPanel.ForEachChild([mPos](Panel& panel) {
			if (panel.contains(mPos))
			{
				if (auto btn = dynamic_cast<Button*>(&panel))
				{
					btn->myOnPressed(*btn);
				}
			}
		});
	}
}

void UILayout::Render(sf::RenderTarget & aRenderTarget)
{
	aRenderTarget.draw(myRootPanel);

	myRootPanel.ForEachChild([this](Panel& panel){
		sf::Vector2f center;
		center.x = panel.GetX() + panel.GetWidth() * 0.5f;
		center.y = panel.GetY() + panel.GetHeight() * 0.5f;
		myDrawer.DrawRectangle(center, panel.GetWidth(), panel.GetHeight());
	});

	aRenderTarget.draw(myDrawer);
	myDrawer.clear();
}

unsigned char UILayout::evaluateDockingFlags(const std::string & aBlock)
{
	unsigned char flags = 0;

	if (aBlock.find("left") != std::string::npos)
		flags |= DockFlag::Left;
	if (aBlock.find("right") != std::string::npos)
		flags |= DockFlag::Right;
	if (aBlock.find("top") != std::string::npos)
		flags |= DockFlag::Top;
	if (aBlock.find("bottom") != std::string::npos)
		flags |= DockFlag::Bottom;
	if (aBlock.find("center") != std::string::npos)
	{
		if (aBlock.find("hcenter") != std::string::npos)
			flags |= DockFlag::HCenter;
		if (aBlock.find("vcenter") != std::string::npos)
			flags |= DockFlag::VCenter;
		if ((!(flags & DockFlag::VCenter) && !(flags & DockFlag::HCenter)))
			flags |= DockFlag::Center;
	}

	return flags;
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
			std::string name = child->FindAttribute("name")->Value();
			float x = child->FindAttribute("x")->FloatValue();
			float y = child->FindAttribute("y")->FloatValue();
			float height = child->FindAttribute("height")->FloatValue();
			float width = child->FindAttribute("width")->FloatValue();
			unsigned char dockFlags = evaluateDockingFlags(child->FindAttribute("dock")->Value());
			std::string image = child->FindAttribute("image")->Value();

			panel = std::make_shared<Panel>(&aParent, name, x, y, width, height, dockFlags);
			if (!image.empty())
				panel->SetImage(image);
		}

		if (panel)
			addChildren(*panel, child);

		aParent.AddPanel(panel);
		child = child->NextSiblingElement();
	}
}
