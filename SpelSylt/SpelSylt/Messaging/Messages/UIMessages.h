#pragma once
#include "SpelSylt/Messaging/Messages/BaseMessage.h"
#include <string>

DEFINE_MSG(SWindowClosedMessage)
DEFINE_MSG_TWOPARAM(SResizedWindowMessage, int, int)