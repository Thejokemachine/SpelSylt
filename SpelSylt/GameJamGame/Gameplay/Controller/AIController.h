#pragma once

#include "GameJamGame/Gameplay/Controller/ControllerInterface.h"

namespace tree
{
	class CWorldProbe;

	class CAIController final
		: public IController
	{
	public:
		CAIController();

		virtual void RegisterPawn(const CPawn& InPawn) const override;
		virtual void Update() override;
		virtual const sf::Vector2f& GetDirection() const;

		const sf::Vector2f& GetTarget() const;

	private:
		CWorldProbe& Probe;
		mutable const CPawn* OwningPawn;

		sf::Vector2f Direction;
		sf::Vector2f Target;
	};
}