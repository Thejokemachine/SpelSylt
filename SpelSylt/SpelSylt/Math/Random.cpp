#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/Math/Random.h"

//------------------------------------------------------------------

Math::CRandom::CRandom(FSeed InSeed)
	: Seed(InSeed)
	, State(0)
{
}

//------------------------------------------------------------------

void Math::CRandom::ResetState()
{
	State = 0;
}

//------------------------------------------------------------------

unsigned int Math::CRandom::BobJenkinsHash()
{
	unsigned int Hash = Seed;
	const unsigned int Depth = State++;

	unsigned int Times = 0;
	while (Times != Depth)
	{
		Times++;
		Hash += Hash << 0x0A;
		Hash ^= Hash >> 0x06;
	}

	Hash += Hash << 0x03;
	Hash ^= Hash >> 0x0B;
	Hash += Hash << 0x0F;

	return Hash;
}

//------------------------------------------------------------------

float Math::CRandom::RandFloat()
{
	unsigned int UVal = BobJenkinsHash();

	const unsigned int ieee32BitMantissaBitmask = 0x007FFFFFu;
	const unsigned int ieeeOne = 0x3F800000u;

	UVal &= ieee32BitMantissaBitmask;
	UVal |= ieeeOne;

	float AsFloat = -1.f;
	float* FloatValPtr = reinterpret_cast<float*>(&UVal);
	AsFloat = *FloatValPtr;
	AsFloat -= 1.0f;

	return AsFloat;
}

//------------------------------------------------------------------

float Math::CRandom::RandFloatInRange(const float InMin, const float InMax)
{
	const float Rand = RandFloat();

	const float Val = InMin + Rand * (InMax - InMin);
	return Val;
}

//------------------------------------------------------------------

sf::Vector2f Math::CRandom::RandVec2InRange(const sf::Vector2f& InMin, const sf::Vector2f& InMax)
{
	sf::Vector2f Val;
	Val.x = RandFloatInRange(InMin.x, InMax.x);
	Val.y = RandFloatInRange(InMin.y, InMax.y);
	return Val;
}

//------------------------------------------------------------------