#pragma once
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Vertex.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

class DebugCommand : public sf::Drawable
{
public:
	DebugCommand() {};
	virtual ~DebugCommand() = default;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
protected:
	sf::Color myColor;
};

class LineCommand : public DebugCommand
{
public:
	LineCommand(const sf::Vector2f& aFrom, const sf::Vector2f& aTo);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	sf::Vertex myLine[2];
};


class RectangleCommand : public DebugCommand
{
public:
	RectangleCommand(const sf::Vector2f& aCenter, float aWidth, float aHeight);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states);
private:
	sf::RectangleShape myRect;
};

/*
class CircleCommand : public DebugCommand
{
public:
	CircleCommand();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states);
};

class TextCommand : public DebugCommand
{
public:
	TextCommand();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states);
};*/