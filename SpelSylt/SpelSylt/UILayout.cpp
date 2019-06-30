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
	myRootPanel.AddPanel(std::make_shared<Panel>(&myRootPanel, "", 15, 15, aWidth * 0.1f, aHeight * 0.1f, DockFlag::Top | DockFlag::Left));
	myRootPanel.AddPanel(std::make_shared<Panel>(&myRootPanel, "", -15, 15, aWidth * 0.1f, aHeight * 0.1f, DockFlag::Top | DockFlag::Right));
	myRootPanel.AddPanel(std::make_shared<Panel>(&myRootPanel, "", -15, -15, aWidth * 0.1f, aHeight * 0.1f, DockFlag::Bottom | DockFlag::Right));
	myRootPanel.AddPanel(std::make_shared<Panel>(&myRootPanel, "", 15, -15, aWidth * 0.1f, aHeight * 0.1f, DockFlag::Bottom | DockFlag::Left));
	auto middle = std::make_shared<Button>(&myRootPanel, "", 15, 15, aWidth * 0.1f, aHeight * 0.1f, DockFlag::Center);
	middle->SetCallback([](Button& button) {
		std::cout << "AAAAAJ" << std::endl;
	});
	myRootPanel.AddPanel(middle);

	XMLDocument layout;
	layout.LoadFile("UI/Layouts/hookGame_layout.xml");
	if (auto root = layout.FirstChildElement("layout"))
	{
		auto child = root->FirstChildElement();
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

				panel = std::make_shared<Panel>(&myRootPanel, name, x, y, width, height, dockFlags);
			}

			myRootPanel.AddPanel(panel);
			child = child->NextSiblingElement();
		}
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
		flags |= DockFlag::Center;

	return flags;
}
