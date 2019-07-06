#pragma once
#include "BaseMessage.h"

#include <string>

struct SResizedWindowMessage
	: public SBaseMessage
{
	SResizedWindowMessage(int aWidth, int aHeight)
		: width(aWidth), height(aHeight)
	{}

	int width = 0;
	int height = 0;
};