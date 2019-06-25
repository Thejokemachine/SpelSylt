#pragma once
#include "System/Vector2.hpp"


#define MAX(a, b) ((a) < (b)) ? (b) : (a)
#define MIN(a, b) ((a) < (b)) ? (a) : (b)
#define CLAMP(a, minimum, maximum) a < minimum ? minimum : (a > maximum ? maximum : a)


namespace Math
{
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

	float Length2(const sf::Vector2f& aVector);
	float Length(const sf::Vector2f& aVector);
	
	 sf::Vector2f Lerp(const sf::Vector2f& aLerpFrom, const sf::Vector2f& aLerpTo, float aInterpolation);

	float Lerp(float aLerpFrom, float aLerpTo, float aInterpolation);

	sf::Vector2f GetNormalized(const sf::Vector2f& aVector);
	void Normalize(sf::Vector2f& aVector);

	//static SColor Lerp(SColor aLerpFrom, SColor aLerpTo, float aInterpolation)
	//{
	//	SColor rv;
	//	rv.r = (aLerpFrom.r + aInterpolation * (aLerpTo.r - aLerpFrom.r));
	//	rv.g = (aLerpFrom.g + aInterpolation * (aLerpTo.g - aLerpFrom.g));
	//	rv.b = (aLerpFrom.b + aInterpolation * (aLerpTo.b - aLerpFrom.b));
	//	rv.a = (aLerpFrom.a + aInterpolation * (aLerpTo.a - aLerpFrom.a));
	//	return rv;
	//}
}