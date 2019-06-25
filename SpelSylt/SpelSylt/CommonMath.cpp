#include "CommonMath.h"
#include <cmath>
#include <utility>

float Math::Length2(const sf::Vector2f & aVector)
{
	float rv = 0;

	rv = aVector.x * aVector.x + aVector.y * aVector.y;

	return rv;
}

float Math::Length(const sf::Vector2f & aVector)
{
	return std::sqrt(Length2(aVector));
}

sf::Vector2f Math::Lerp(const sf::Vector2f & aLerpFrom, const sf::Vector2f & aLerpTo, float aInterpolation)
{
	sf::Vector2f rv;

	rv.x = Lerp(aLerpFrom.x, aLerpTo.x, aInterpolation);
	rv.y = Lerp(aLerpFrom.y, aLerpTo.y, aInterpolation);

	return std::move(rv);
}

float Math::Lerp(float aLerpFrom, float aLerpTo, float aInterpolation)
{
	return (aLerpFrom + aInterpolation * (aLerpTo - aLerpFrom));
}

sf::Vector2f Math::GetNormalized(const sf::Vector2f & aVector)
{
	sf::Vector2f rv = aVector;
	Normalize(rv);
	return rv;
}

void Math::Normalize(sf::Vector2f & aVector)
{
	float length = Length(aVector);
	if (length != 0)
	{
		aVector.x /= length;
		aVector.y /= length;
	}
}
