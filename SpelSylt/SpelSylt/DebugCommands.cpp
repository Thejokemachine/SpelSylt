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

RectangleCommand::RectangleCommand(const sf::Vector2f & aCenter, float aWidth, float aHeight, bool aFill)
{
	myRect.setPosition(aCenter);
	myRect.setOrigin(aWidth * 0.5f, aHeight * 0.5f);
	myRect.setSize(sf::Vector2f(aWidth, aHeight));
	myRect.setOutlineThickness(1);
	if (!aFill) myRect.setFillColor(sf::Color::Transparent);
}

void RectangleCommand::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(myRect);
}

CircleCommand::CircleCommand(const sf::Vector2f & aPosition, float aRadius, bool aFill)
{
	myCircle.setPosition(aPosition);
	myCircle.setOrigin(aRadius, aRadius);
	myCircle.setRadius(aRadius);
	myCircle.setOutlineThickness(1);
	if (!aFill) myCircle.setFillColor(sf::Color::Transparent);
}

void CircleCommand::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(myCircle);
}

TextCommand::TextCommand(const sf::Font& aFont, const std::string & aText, const sf::Vector2f & aPosition, short aSize)
{
	myText.setCharacterSize(aSize);
	myText.setString(aText);
	myText.setPosition(aPosition);
	myText.setFont(aFont);
}

void TextCommand::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(myText);
}
