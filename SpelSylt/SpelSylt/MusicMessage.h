#pragma once

#include "BaseMessage.h"

#include <string>

struct SMusicMessage
	: public SBaseMessage
{
	SMusicMessage(const std::string& InAlias, bool InFadeOutCurrent)
		: Alias(InAlias)
		, FadeOutCurrent(InFadeOutCurrent)
	{
	}

	std::string Alias;
	bool FadeOutCurrent;
};