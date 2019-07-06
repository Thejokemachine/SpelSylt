#pragma once

#include "BaseMessage.h"

#include <string>

struct SSoundMessage
	: public SBaseMessage
{
	SSoundMessage(const std::string& InAlias)
		: Alias(InAlias)
	{}

	std::string Alias;
};