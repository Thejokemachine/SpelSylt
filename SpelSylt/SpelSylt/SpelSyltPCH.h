#pragma once

//Standard Library
#include <utility>
#include <string>

//Logging
#include "SpelSylt/Debugging/Logging/DebugLogger.h"

//Memory
#include "SpelSylt/Memory/MemAllocSizes.h"

//Contexts
#include "SpelSylt/Contexts/GameContext.h"
#include "SpelSylt/Contexts/RenderingContext.h"

//Utility
#include "SpelSylt/Utility/Time/TimeGetter.h"
#include "SpelSylt/Utility/Input/InputEventGetter.h"
#include "SpelSylt/FileHandling/Loading/LoaderInterface.h"

//Asset
#include "SpelSylt/FileHandling/Asset/Assets.h"

//Messaging
#include "SpelSylt/Messaging/MessageQueue.h"
#include "SpelSylt/Messaging/Subscribing/SubscriptionHandle.h"

//Messages
#include "SpelSylt/Messaging/Messages/AudioMessages.h"
