#pragma once

//Logging
#include <SpelSylt/Debugging/Logging/DebugLogger.h>

//Messaging
#include <SpelSylt/Messaging/Messages/BaseMessage.h>
#include <SpelSylt/Messaging/MessageQueue.h>

//Contexts
#include <SpelSylt/Contexts/GameContext.h>
#include <SpelSylt/Contexts/RenderingContext.h>

//Rendering
#include <SpelSylt/Rendering/RenderCommand.h>
#include <SpelSylt/Rendering/RenderQueueInput.h>
#include <SpelSylt/Debugging/Rendering/DebugDrawerInput.h>

//File handling
#include <SpelSylt/FileHandling/Loading/LoaderInterface.h>

//Banks
#include <SpelSylt/FileHandling/Banks/TextureProviderInterface.h>
#include <SpelSylt/FileHandling/Banks/FontBank.h>

//Utility
#include <SpelSylt/Utility/Time/TimeGetter.h>
#include <SpelSylt/Utility/Input/InputEventGetter.h>

//Math
#include <SpelSylt/Math/CommonMath.h>

//SFML
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/View.hpp>