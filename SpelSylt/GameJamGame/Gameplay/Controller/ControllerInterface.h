#pragma once
#include <SFML/System/Vector2.hpp>

namespace tree
{
	class IController
	{
	public:
		virtual void Update() = 0;
		virtual const sf::Vector2f& GetDirection() const = 0;
	};
}