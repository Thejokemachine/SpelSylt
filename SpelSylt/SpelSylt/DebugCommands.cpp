#include "SpelSyltPCH.h"

#include "DebugCommands.h"
#include "SFML/Graphics/RenderTarget.hpp"

LineCommand::LineCommand(const sf::Vector2f & aFrom, const sf::Vector2f & aTo, const sf::Color& aColor)
{
	myLine[0].position = aFrom;
	myLine[0].color = aColor;
	myLine[1].position = aTo;
	myLine[1].color = aColor;
}

void LineCommand::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(myLine, 2, sf::PrimitiveType::Lines);
}

RectangleCommand::RectangleCommand(const sf::Vector2f & aCenter, float aWidth, float aHeight, bool aFill, const sf::Color& aColor)
{
	myRect.setPosition(aCenter);
	myRect.setOrigin(aWidth * 0.5f, aHeight * 0.5f);
	myRect.setSize(sf::Vector2f(aWidth, aHeight));
	myRect.setOutlineThickness(1);
	myRect.setOutlineColor(aColor);
	myRect.setFillColor(aColor);
	if (!aFill) myRect.setFillColor(sf::Color::Transparent);
}

void RectangleCommand::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(myRect);
}

CircleCommand::CircleCommand(const sf::Vector2f & aPosition, float aRadius, bool aFill, const sf::Color& aColor)
{
	myCircle.setPosition(aPosition);
	myCircle.setOrigin(aRadius, aRadius);
	myCircle.setRadius(aRadius);
	myCircle.setOutlineThickness(1);
	myCircle.setOutlineColor(aColor);
	myCircle.setFillColor(aColor);
	if (!aFill) myCircle.setFillColor(sf::Color::Transparent);
}

void CircleCommand::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(myCircle);
}

TextCommand::TextCommand(const sf::Font& aFont, const std::string & aText, const sf::Vector2f & aPosition, const sf::Color& aColor, short aSize)
{
	myText.setCharacterSize(aSize);
	myText.setString(aText);
	myText.setPosition(aPosition);
	myText.setFont(aFont);
	myText.setFillColor(aColor);
}

void TextCommand::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(myText);
}
