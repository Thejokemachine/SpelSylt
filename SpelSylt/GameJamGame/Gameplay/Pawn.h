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
		void Tick(float InDT);

		const sf::Vector2f& GetPosition() const;
	private:
		sf::Vector2f Position;
		float Speed;
		const IController* Controller;
	};
}