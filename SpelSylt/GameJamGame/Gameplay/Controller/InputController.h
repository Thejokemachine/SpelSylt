#pragma once
#include "GameJamGame/Gameplay/Controller/ControllerInterface.h"

namespace SpelSylt
{
	class IInputEventGetter;
}

namespace tree
{
	class CInputController final
		: public IController
	{
	public:
		CInputController(const SpelSylt::IInputEventGetter& InInputGetter);
		virtual void Update() override;
		virtual const sf::Vector2f& GetDirection() const;
	private:
		const SpelSylt::IInputEventGetter& InputGetter;
		sf::Vector2f CurrentDirection;
	};
}
