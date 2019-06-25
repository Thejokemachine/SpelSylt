#pragma once
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Font.hpp"

#include <vector>

#define DEBUG_COLOR sf::Color::White

class DebugCommand;
class LineCommand;
class RectangleCommand;
class CircleCommand;
class TextCommand;

class DebugDrawer : public sf::Drawable
{
public:
	DebugDrawer();
	~DebugDrawer();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void clear();

	void DrawLine(const sf::Vector2f& aFrom, const sf::Vector2f& aTo, const sf::Color& aColor = DEBUG_COLOR);
	void DrawRectangle(const sf::Vector2f & aCenter, float aWidth, float aHeight, bool aFill = false, const sf::Color& aColor = DEBUG_COLOR);
	void DrawCircle(const sf::Vector2f& aPosition, float aRadius, bool aFill = false, const sf::Color& aColor = DEBUG_COLOR);
	void DrawText(const std::string& aText, const sf::Vector2f& aPosition, const sf::Color& aColor = DEBUG_COLOR);

private:

	void AddCommand(DebugCommand* command);
	std::vector<DebugCommand*> myCommands;

	sf::Font myFont;
};

