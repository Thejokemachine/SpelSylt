#pragma once

#include "BaseMessage.h"
#include <string>

DEFINE_MSG_TWOPARAM(SMusicMessage, std::string, bool)
DEFINE_MSG_ONEPARAM(SSoundMessage, std::string)