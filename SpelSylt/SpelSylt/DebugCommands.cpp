#include "DebugCommands.h"
#include "SFML/Graphics/RenderTarget.hpp"

LineCommand::LineCommand(const sf::Vector2f & aFrom, const sf::Vector2f & aTo)
{
	myLine[0].position = aFrom;
	myLine[1].position = aTo;
}

void LineCommand::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(myLine, 2, sf::PrimitiveType::Lines);
}

RectangleCommand::RectangleCommand(const sf::Vector2f & aCenter, float aWidth, float aHeight)
{
}
