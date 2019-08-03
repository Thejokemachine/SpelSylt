#pragma once
#include <SFML/System/Vector2.hpp>

namespace tree
{
	class IController;

	class CPawn
	{
	public:
		CPawn();

		void SetSpeed(float InSpeed);

		void AttachController(const IController& InController);
		virtual void Tick(float InDT);

		const sf::Vector2f& GetPosition() const;
	protected:
		sf::Vector2f Position;
		float Speed;
		const IController* Controller;
	};
}