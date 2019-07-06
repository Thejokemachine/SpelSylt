#pragma once

#include "BaseEvent.h"
#include <functional>

class IEventSubscriberList
{
public:
	virtual void DispatchToAllSubscribers(const SBaseEvent* InEvent) = 0;
};