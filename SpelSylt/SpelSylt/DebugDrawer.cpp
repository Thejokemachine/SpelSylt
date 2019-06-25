#include "DebugDrawer.h"

#include "DebugCommands.h"


DebugDrawer::DebugDrawer()
{
	myFont.loadFromFile("Graphics/Fonts/default.ttf");
}


DebugDrawer::~DebugDrawer()
{
}

void DebugDrawer::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (auto&& command : myCommands)
	{
		command->draw(target, states);
		delete command;
	}
}

void DebugDrawer::clear()
{
	myCommands.clear();
}

void DebugDrawer::DrawLine(const sf::Vector2f & aFrom, const sf::Vector2f & aTo)
{
	AddCommand(new LineCommand(aFrom, aTo));
}

void DebugDrawer::DrawRectangle(const sf::Vector2f & aCenter, float aWidth, float aHeight)
{
	AddCommand(new RectangleCommand(aCenter, aWidth, aHeight));
}

void DebugDrawer::DrawCircle(const sf::Vector2f & aPosition, float aRadius)
{
	AddCommand(new CircleCommand(aPosition, aRadius));
}

void DebugDrawer::DrawText(const std::string & aText, const sf::Vector2f & aPosition)
{
	AddCommand(new TextCommand(myFont, aText, aPosition));
}

void DebugDrawer::AddCommand(DebugCommand * command)
{
	myCommands.push_back(command);
}
