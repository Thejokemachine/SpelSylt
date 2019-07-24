#pragma once

#include "SpelSylt/Messaging/Messages/BaseMessage.h"
#include <functional>

namespace SpelSylt
{
	struct SSubscriptionHandle;

	class IMessageSubscriberList
	{
	public:
		virtual void Unsubscribe(const SSubscriptionHandle& InHandle) = 0;
		virtual void DispatchToAllSubscribers(const SBaseMessage* InEvent) = 0;
	};
}

namespace SS = SpelSylt;