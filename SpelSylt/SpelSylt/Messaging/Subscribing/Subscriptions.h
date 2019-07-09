#pragma once

#include "SpelSylt/Messaging/Subscribing/SubscriptionHandle.h"
#include <vector>

class CSubscriptions
{
public:
	CSubscriptions();
	~CSubscriptions();
	void AddSubscription(const SSubscriptionHandle& InHandle);
private:
	std::vector<SSubscriptionHandle> Handles;

};