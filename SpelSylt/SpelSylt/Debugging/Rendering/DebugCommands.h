#pragma once
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Vertex.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Text.hpp"

namespace SpelSylt
{
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
		LineCommand(const sf::Vector2f& aFrom, const sf::Vector2f& aTo, const sf::Color& aColor);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	private:
		sf::Vertex myLine[2];
	};

	class RectangleCommand : public DebugCommand
	{
	public:
		RectangleCommand(const sf::Vector2f& aPosition, float aWidth, float aHeight, bool aFill, const sf::Color& aColor);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	private:
		sf::RectangleShape myRect;
	};

	class CircleCommand : public DebugCommand
	{
	public:
		CircleCommand(const sf::Vector2f& aPosition, float aRadius, bool aFill, const sf::Color& aColor);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	private:
		sf::CircleShape myCircle;
	};

	class TextCommand : public DebugCommand
	{
	public:
		TextCommand(const sf::Font& aFont, const std::string& aText, const sf::Vector2f& aPosition, const sf::Color& aColor, short aSize = 32);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	private:
		sf::Text myText;
	};
}

namespace SS = SpelSylt;