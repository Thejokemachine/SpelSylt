#pragma once
#include <string>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

class IDebugDrawerInput
{
public:
	virtual void DrawLine(const sf::Vector2f& aFrom, const sf::Vector2f& aTo, const sf::Color& aColor = sf::Color::White) = 0;
	virtual void DrawRectangle(const sf::Vector2f& aCenter, float aWidth, float aHeight, bool aFill = false, const sf::Color& aColor = sf::Color::White) = 0;
	virtual void DrawCircle(const sf::Vector2f& aPosition, float aRadius, bool aFill = false, const sf::Color& aColor = sf::Color::White) = 0;
	virtual void DrawText(const std::string& aText, const sf::Vector2f& aPosition, const sf::Color& aColor = sf::Color::White) = 0;
};