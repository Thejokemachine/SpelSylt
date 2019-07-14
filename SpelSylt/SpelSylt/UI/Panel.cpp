#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/UI/Panel.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SpelSylt/UI/Base/UILayout.h"
#include "SpelSylt/XMLUtilities.h"
#include "SpelSylt/UI/UIUtilities.h"

#include <unordered_map>

using namespace UI;

Panel::Panel(UILayout & aLayout, const Panel * aParent, const std::string & aName, float x, float y, float aWidth, float aHeight, unsigned char aDockFlags, tinyxml2::XMLElement & aElement) :
sf::FloatRect(0, 0, aWidth, aHeight),
myLayout(aLayout),
myXMLElement(aElement),
myParent(aParent)
{
	setDirty();
}

Panel::Panel(UILayout& aLayout, const Panel* aParent, tinyxml2::XMLElement& aElement) :
sf::FloatRect(0, 0, 0, 0),
myLayout(aLayout),
myXMLElement(aElement),
myParent(aParent)
{
	std::string image, dockFlagsValue, colorValue;

	XMLUtilities::QueryAttribute(myXMLElement, "name", myName);
	XMLUtilities::QueryAttribute(myXMLElement, "dock", dockFlagsValue);
	XMLUtilities::QueryAttribute(myXMLElement, "image", image);
	XMLUtilities::QueryAttribute(myXMLElement, "color", colorValue);

	myDockFlags = UIUtilities::EvaluateDockingFlags(dockFlagsValue);
	myColor = UIUtilities::EvaluateColor(colorValue);
	SetColor(myColor);
	if (!image.empty())
		SetImage(image);

	setDirty();
}

Panel * Panel::GetPanel(const std::string & aName)
{
	Panel* rv = nullptr;
	if (myName == aName)
		rv = this;

	if (rv == nullptr)
	{
		for (auto& p : myChildren)
		{
			if (p->myName == aName)
			{
				rv = p.get();
				break;
			}
		}
		for (auto& p : myChildren)
		{
			rv = p->GetPanel(aName);
			if (rv)
			{
				break;
			}
		}
	}
	return rv;
}

void Panel::SetImage(const std::string & aImage)
{
	myTexture.loadFromFile("UI/Images/" + aImage + ".png");
}

void Panel::SetColor(const sf::Color & aColor)
{
	myColor = aColor;
}

void UI::Panel::SetBounds(float x, float y, float width, float height)
{
	this->left = x;
	this->top = y;
	this->width = width;
	this->height = height;

	ForEachChild([](Panel& p) { 
		p.Layout();
	});
}

void Panel::AddPanel(std::shared_ptr<Panel> aPanel)
{
	myChildren.emplace_back(aPanel);
}

void UI::Panel::Layout()
{
	std::string sx;
	std::string sy;
	std::string sheight;
	std::string swidth;

	XMLUtilities::QueryAttribute(myXMLElement, "x", sx);
	XMLUtilities::QueryAttribute(myXMLElement, "y", sy);
	XMLUtilities::QueryAttribute(myXMLElement, "width", swidth);
	XMLUtilities::QueryAttribute(myXMLElement, "height", sheight);

	myX = evaluateExpression(sx);
	myY = evaluateExpression(sy);
	width = evaluateExpression(swidth);
	height = evaluateExpression(sheight);

	left = 0.f;
	top = 0.f;

	if (myParent)
	{
		sf::Vector2f dockOffset;
		if (myDockFlags & DockFlag::Bottom)
		{
			dockOffset.y = -height;
			dockOffset.y += myParent->GetHeight();
		}
		if (myDockFlags & DockFlag::Right)
		{
			dockOffset.x = -width;
			dockOffset.x += myParent->GetWidth();
		}
		if (myDockFlags & DockFlag::Center)
		{
			dockOffset = sf::Vector2f(-width * 0.5f, -height * 0.5f);
			dockOffset += sf::Vector2f(myParent->GetWidth()*0.5f, myParent->GetHeight()*0.5f);
		}
		if (myDockFlags & DockFlag::HCenter)
		{
			dockOffset.x = -width * 0.5f + myParent->GetWidth() * 0.5f;
		}
		if (myDockFlags & DockFlag::VCenter)
		{
			dockOffset.y = -height * 0.5f + myParent->GetHeight() * 0.5f;
		}

		left += dockOffset.x;
		top += dockOffset.y;

		left += myParent->GetX();
		top += myParent->GetY();
	}
	left += myX;
	top += myY;

	onLayout();

	for (auto& p : myChildren)
		p->Layout();

	myIsDirty = false;
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

void UI::Panel::setDirty()
{
	myIsDirty = true;
}

float UI::Panel::evaluateExpression(const std::string & aAttributeBlock)
{
	if (aAttributeBlock.empty())
		return 0.f;

	if (aAttributeBlock[0] != '{')
		return std::stof(aAttributeBlock);

	const std::unordered_map<std::string, float> variables = {
		{"parent.width", myParent->GetWidth()},
		{"parent.height", myParent->GetHeight()}
	};
// 	static const char operations[] = {
// 		'-',
// 		'+',
// 		'*',
// 		'/'
// 	};

	const std::string block = UIUtilities::RemoveWhiteSpace(aAttributeBlock);

	enum Operation : char {
		Subtract = '-',
		Add = '+',
		Multiply = '*',
		Divide = '/'
	};

	std::vector<char> operations;

	std::string newBlock = "";
	for (auto&& c : block)
	{
		if (c == '{' || c == '}')
			continue;

		if (c != Subtract && c != Add && c != Multiply && c != Divide)
		{
			newBlock += c;
		}
		else
		{
			newBlock += ' ';
			operations.emplace_back(c);
		}
	}

	auto variableOrder = UIUtilities::SplitString(newBlock, ' ');

	float leftV = 0.f;
	float rightV = 0.f;
	float evaluatedValue = 0.f;

	if (variableOrder.size() >= 1)
	{
		if (variables.find(variableOrder[0]) != variables.end())
			leftV = variables.at(variableOrder[0]);
		else
			leftV = std::stof(variableOrder[0]);

		evaluatedValue = leftV;
	}
	if (variableOrder.size() == 2)
	{
		if (variables.find(variableOrder[1]) != variables.end())
			rightV = variables.at(variableOrder[1]);
		else
			rightV = std::stof(variableOrder[1]);

		switch (operations[0])
		{
		case '-':
			evaluatedValue = leftV - rightV;
			break;
		case '+':
			evaluatedValue = leftV + rightV;
			break;
		case '*':
			evaluatedValue = leftV * rightV;
			break;
		case '/':
			evaluatedValue = leftV / rightV;
			break;
		}
	}

	return evaluatedValue;
}
