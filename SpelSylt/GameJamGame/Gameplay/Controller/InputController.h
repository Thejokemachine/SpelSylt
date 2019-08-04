#pragma once
#include "GameJamGame/Gameplay/Controller/ControllerInterface.h"

namespace SpelSylt
{
	class IInputEventGetter;
	class CMessageQueue;
}

namespace tree
{
	class CInputController final
		: public IController
	{
	public:
		CInputController(const SpelSylt::IInputEventGetter& InInputGetter, SpelSylt::CMessageQueue& InMessageQueue);

		virtual void RegisterPawn(const CPawn& InPawn) const override;
		virtual void Update() override;
		virtual const sf::Vector2f& GetVelocity() const;
	private:
		const SpelSylt::IInputEventGetter& InputGetter;
		sf::Vector2f CurrentVelocity;

		mutable const CPawn* OwningPawn;

		SpelSylt::CMessageQueue& MessageQueue;
	};
}
