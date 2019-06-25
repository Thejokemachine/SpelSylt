#include "DebugDrawer.h"

#include "DebugCommands.h"


DebugDrawer::DebugDrawer()
{
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

void DebugDrawer::AddCommand(DebugCommand * command)
{
	myCommands.push_back(command);
}
