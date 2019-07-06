#pragma once

#include "BaseEvent.h"

struct STestEvent
	: public SBaseEvent
{
	STestEvent(int InInteger, float InFloat)
		: TestInteger(InInteger)
		, TestFloat(InFloat)
	{}
	
	int TestInteger;
	float TestFloat;
};