#pragma once
#include <random>
#include "SFML/System/Vector2.hpp"

#define M_PI 3.141592654f

#define MAX(a, b) ((a) < (b)) ? (b) : (a)
#define MIN(a, b) ((a) < (b)) ? (a) : (b)
#define CLAMP(a, minimum, maximum) a < minimum ? minimum : (a > maximum ? maximum : a)


namespace Math
{
	template<typename T>
	T Sign(T aValue)
	{
		return aValue > 0 ? 1 : -1;
	}

	template<typename T>
	T Max(T aValue0, T aValue1)
	{
		return MAX(aValue0, aValue1);
	}

	template<typename T>
	T Min(T aValue0, T aValue1)
	{
		return MIN(aValue0, aValue1);
	}

	template<typename T>
	T Clamp(T aValueToClamp, T aMin, T aMax)
	{
		return CLAMP(aValueToClamp, aMin, aMax);
	}

	static float ToDegrees(float aInRadians)
	{
		return (aInRadians * 180.f) / M_PI;
	}

	static float ToRadians(float aInDegree)
	{
		return (aInDegree * M_PI) / 180.f;
	}

	static float Dot(const sf::Vector2f& InVecOne, const sf::Vector2f& InVecTwo)
	{
		return (InVecOne.x * InVecTwo.x) + (InVecOne.y * InVecTwo.y);
	}

	float Length2(const sf::Vector2f& aVector);
	float Length(const sf::Vector2f& aVector);
	
	 sf::Vector2f Lerp(const sf::Vector2f& aLerpFrom, const sf::Vector2f& aLerpTo, float aInterpolation);

	float Lerp(float aLerpFrom, float aLerpTo, float aInterpolation);

	sf::Vector2f GetNormalized(const sf::Vector2f& aVector);
	void Normalize(sf::Vector2f& aVector);

	float RandomInRange(float Min, float Max);

	static sf::Color LerpColor(const sf::Color& aLerpFrom, const sf::Color& aLerpTo, float aInterpolation)
	{
		const float FromR = static_cast<float>(aLerpFrom.r);
		const float FromG = static_cast<float>(aLerpFrom.g);
		const float FromB = static_cast<float>(aLerpFrom.b);
		const float FromA = static_cast<float>(aLerpFrom.a);

		const float ToR = static_cast<float>(aLerpTo.r);
		const float ToG = static_cast<float>(aLerpTo.g);
		const float ToB = static_cast<float>(aLerpTo.b);
		const float ToA = static_cast<float>(aLerpTo.a);

		sf::Color rv;
		rv.r = static_cast<sf::Uint8>(aLerpFrom.r + aInterpolation * (ToR - FromR));
		rv.g = static_cast<sf::Uint8>(aLerpFrom.g + aInterpolation * (ToG - FromG));
		rv.b = static_cast<sf::Uint8>(aLerpFrom.b + aInterpolation * (ToB - FromB));
		rv.a = static_cast<sf::Uint8>(aLerpFrom.a + aInterpolation * (ToA - FromA));
		return rv;
	}
}