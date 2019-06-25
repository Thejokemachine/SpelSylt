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

void DebugDrawer::DrawLine(const sf::Vector2f & aFrom, const sf::Vector2f & aTo, const sf::Color& aColor)
{
	AddCommand(new LineCommand(aFrom, aTo, aColor));
}

void DebugDrawer::DrawRectangle(const sf::Vector2f & aCenter, float aWidth, float aHeight, bool aFill, const sf::Color& aColor)
{
	AddCommand(new RectangleCommand(aCenter, aWidth, aHeight, aFill, aColor));
}

void DebugDrawer::DrawCircle(const sf::Vector2f & aPosition, float aRadius, bool aFill, const sf::Color& aColor)
{
	AddCommand(new CircleCommand(aPosition, aRadius, aFill, aColor));
}

void DebugDrawer::DrawText(const std::string & aText, const sf::Vector2f & aPosition, const sf::Color& aColor)
{
	AddCommand(new TextCommand(myFont, aText, aPosition, aColor));
}

void DebugDrawer::AddCommand(DebugCommand * command)
{
	myCommands.push_back(command);
}
