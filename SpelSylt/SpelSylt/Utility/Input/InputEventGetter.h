#pragma once
#include "SpelSylt/Utility/Input/KeyCodes.h"

#include <SFML/System/Vector2.hpp>

#include <string>

namespace SpelSylt
{
	class IInputEventGetter
	{
	public:
		virtual bool IsKeyPressed(EKeyCode aKey) const = 0;
		virtual bool IsKeyDown(EKeyCode aKey) const = 0;
		virtual bool IsKeyReleased(EKeyCode aKey) const = 0;

		virtual int GetScrollWheelDelta() const = 0;
		virtual sf::Vector2f GetMousePosFloat() const = 0;
		virtual sf::Vector2i GetMousePosInt() const = 0;

		virtual std::string GetTextInput() const = 0;
	};
}

namespace SS = SpelSylt;