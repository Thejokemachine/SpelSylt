#pragma once
#include "SpelSylt/Debugging/Rendering/DebugDrawerInput.h"

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Font.hpp"

#include <vector>

#define DEBUG_COLOR sf::Color::White

namespace SpelSylt
{
	class DebugCommand;
	class LineCommand;
	class RectangleCommand;
	class CircleCommand;
	class TextCommand;

	class CDebugDrawer final
		: public sf::Drawable
		, public IDebugDrawerInput
	{
	public:
		CDebugDrawer();
		~CDebugDrawer();

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		void clear();

		//Begin IDebugDrawerInput
		virtual void DrawLine(const sf::Vector2f& aFrom, const sf::Vector2f& aTo, const sf::Color& aColor = DEBUG_COLOR) override;
		virtual void DrawRectangle(const sf::Vector2f & aCenter, float aWidth, float aHeight, bool aFill = false, const sf::Color& aColor = DEBUG_COLOR) override;
		virtual void DrawCircle(const sf::Vector2f& aPosition, float aRadius, bool aFill = false, const sf::Color& aColor = DEBUG_COLOR) override;
		virtual void DrawText(const std::string& aText, const sf::Vector2f& aPosition, const sf::Color& aColor = DEBUG_COLOR) override;
		//End IDebugDrawerInput

	private:

		void AddCommand(DebugCommand* command);
		std::vector<DebugCommand*> myCommands;

		sf::Font myFont;
	};
}

namespace SS = SpelSylt;