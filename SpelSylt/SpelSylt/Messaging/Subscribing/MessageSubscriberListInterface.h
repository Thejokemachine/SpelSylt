#pragma once

#include "Messaging/Messages/BaseMessage.h"
#include <functional>

struct SSubscriptionHandle;

class IMessageSubscriberList
{
public:
	virtual void Unsubscribe(const SSubscriptionHandle& InHandle) = 0;
	virtual void DispatchToAllSubscribers(const SBaseMessage* InEvent) = 0;
};