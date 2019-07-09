#pragma once
#include "SpelSylt/Utility/Input/KeyCodes.h"

#include <SFML/System/Vector2.hpp>

class IInputEventGetter
{
public:
	virtual bool IsKeyPressed(EKeyCode aKey) = 0;
	virtual bool IsKeyDown(EKeyCode aKey) = 0;
	virtual bool IsKeyReleased(EKeyCode aKey) = 0;

	virtual int GetScrollWheelDelta() = 0;
	virtual sf::Vector2f GetMousePosFloat() = 0;
	virtual sf::Vector2i GetMousePosInt() = 0;

	virtual std::string GetTextInput() = 0;
};