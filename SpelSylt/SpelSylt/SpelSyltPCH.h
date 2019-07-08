#pragma once

//Standard Library
#include <utility>
#include <string>

//Logging
#include "Debugging/Logging/DebugLogger.h"

//Memory
#include "Memory/MemAllocSizes.h"

//Contexts
#include "Contexts/GameContext.h"
#include "Contexts/RenderingContext.h"

//Utility
#include "Utility/Time/TimeGetter.h"
#include "Utility/Input/InputEventGetter.h"
#include "FileHandling/Loading/AsyncLoaderInterface.h"

//Asset
#include "FileHandling/Asset/Assets.h"

//Messaging
#include "Messaging/MessageQueue.h"
#include "Messaging/Subscribing/SubscriptionHandle.h"

//Messages
#include "Messaging/Messages/AudioMessages.h"