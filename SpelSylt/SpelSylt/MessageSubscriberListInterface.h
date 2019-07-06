#pragma once

#include "BaseEvent.h"
#include <functional>

struct SSubscriptionHandle;

class IMessageSubscriberList
{
public:
	virtual void Unsubscribe(const SSubscriptionHandle& InHandle) = 0;
	virtual void DispatchToAllSubscribers(const SBaseEvent* InEvent) = 0;
};