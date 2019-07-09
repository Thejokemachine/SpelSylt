#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/Debugging/Rendering/DebugDrawer.h"

#include "SpelSylt/Debugging/Rendering/DebugCommands.h"


CDebugDrawer::CDebugDrawer()
{
	myFont.loadFromFile("Graphics/Fonts/default.ttf");
}


CDebugDrawer::~CDebugDrawer()
{
}

void CDebugDrawer::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (auto&& command : myCommands)
	{
		command->draw(target, states);
		delete command;
	}
}

void CDebugDrawer::clear()
{
	myCommands.clear();
}

void CDebugDrawer::DrawLine(const sf::Vector2f & aFrom, const sf::Vector2f & aTo, const sf::Color& aColor)
{
	AddCommand(new LineCommand(aFrom, aTo, aColor));
}

void CDebugDrawer::DrawRectangle(const sf::Vector2f & aCenter, float aWidth, float aHeight, bool aFill, const sf::Color& aColor)
{
	AddCommand(new RectangleCommand(aCenter, aWidth, aHeight, aFill, aColor));
}

void CDebugDrawer::DrawCircle(const sf::Vector2f & aPosition, float aRadius, bool aFill, const sf::Color& aColor)
{
	AddCommand(new CircleCommand(aPosition, aRadius, aFill, aColor));
}

void CDebugDrawer::DrawText(const std::string & aText, const sf::Vector2f & aPosition, const sf::Color& aColor)
{
	AddCommand(new TextCommand(myFont, aText, aPosition, aColor));
}

void CDebugDrawer::AddCommand(DebugCommand * command)
{
	myCommands.push_back(command);
}
