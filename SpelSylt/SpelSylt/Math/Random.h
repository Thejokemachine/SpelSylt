#pragma once
#include <SFML/System/Vector2.hpp>

namespace Math
{
	using FSeed = unsigned int;

	class CRandom
	{
	public:
		CRandom(FSeed InSeed);

		void ResetState();

		float RandFloat();
		float RandFloatInRange(const float InMin, const float InMax);
		sf::Vector2f RandVec2InRange(const sf::Vector2f& InMin, const sf::Vector2f& InMax);

	private:
		unsigned int BobJenkinsHash();

		const FSeed Seed;
		unsigned int State;
	};
}