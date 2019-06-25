#pragma once
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Font.hpp"

#include <vector>

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

	void DrawLine(const sf::Vector2f& aFrom, const sf::Vector2f& aTo);
	void DrawRectangle(const sf::Vector2f & aCenter, float aWidth, float aHeight);
	void DrawCircle(const sf::Vector2f& aPosition, float aRadius);
	void DrawText(const std::string& aText, const sf::Vector2f& aPosition);

private:

	void AddCommand(DebugCommand* command);
	std::vector<DebugCommand*> myCommands;

	sf::Font myFont;
};

