#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/UI/Panel.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SpelSylt/UI/Base/UILayout.h"

using namespace UI;

Panel::Panel(UILayout& aLayout, const Panel* aParent, const std::string& aName, float x, float y, float aWidth, float aHeight, unsigned char aDockFlags, tinyxml2::XMLElement& aElement) :
sf::FloatRect(x, y, aWidth, aHeight),
myLayout(aLayout),
myXMLElement(aElement),
myParent(aParent),
myName(aName),
myDockFlags(aDockFlags)
{
	if (myParent)
	{
		sf::Vector2f dockOffset;
		if (myDockFlags & DockFlag::Bottom)
		{
			dockOffset.y = -aHeight;
			dockOffset.y += myParent->GetHeight();
		}
		if (myDockFlags & DockFlag::Right)
		{
			dockOffset.x = -aWidth;
			dockOffset.x += myParent->GetWidth();
		}
		if (myDockFlags & DockFlag::Center)
		{
			dockOffset = sf::Vector2f(-aWidth * 0.5f, -aHeight * 0.5f);
			dockOffset += sf::Vector2f(myParent->GetWidth()*0.5f, myParent->GetHeight()*0.5f);
		}
		if (myDockFlags & DockFlag::HCenter)
		{
			dockOffset.x = -aWidth * 0.5f + myParent->GetWidth() * 0.5f;
		}
		if (myDockFlags & DockFlag::VCenter)
		{
			dockOffset.y = -aHeight * 0.5f + myParent->GetHeight() * 0.5f;
		}

		left += dockOffset.x;
		top += dockOffset.y;

		left += myParent->GetX();
		top += myParent->GetY();
	}
	left += x;
	top += y;
}

Panel * Panel::GetPanel(const std::string & aName)
{
	for (auto& p : myChildren)
	{
		if (p->myName == aName)
		{
			return p.get();
		}
	}
	for (auto& p : myChildren)
	{
		return p->GetPanel(aName);
	}
	return nullptr;
}

void Panel::SetImage(const std::string & aImage)
{
	myTexture.loadFromFile("UI/Images/" + aImage + ".png");
}

void Panel::SetColor(const sf::Color & aColor)
{
	myColor = aColor;
}

void Panel::AddPanel(std::shared_ptr<Panel> aPanel)
{
	myChildren.emplace_back(aPanel);
}

void UI::Panel::Resize(float aWidth, float aHeight)
{

	for (auto& p : myChildren)
		p->Resize(GetWidth(), GetHeight());
}

void Panel::ForEachChild(std::function<void(Panel& panel)> aFunction)
{
	for (auto& panel : myChildren)
	{
		panel->ForEachChild(aFunction);
		aFunction(*panel);
	}
}

void Panel::Update(const float dt)
{
	onUpdate(dt);
}

void Panel::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (myTexture.getSize().x > 0)
	{
		sf::Sprite sprite;
		sprite.setTexture(myTexture);
		sprite.setPosition(left, top);
		sprite.setScale(width / myTexture.getSize().x, height / myTexture.getSize().y);
		sprite.setColor(myColor);

		target.draw(sprite, states);
	}

	onDraw(target);

	for (auto& panel : myChildren)
	{
		panel->draw(target, states);
	}
}
