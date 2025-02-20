#pragma once

#include "SpelSylt/Messaging/Messages/BaseMessage.h"
#include <string>

namespace SpelSylt
{
	DEFINE_MSG_TWOPARAM(SMusicMessage, std::string, bool)
	DEFINE_MSG_ONEPARAM(SSoundMessage, std::string)
}