#pragma once

#include "SpelSylt/Messaging/Subscribing/SubscriptionHandle.h"
#include <vector>

namespace SpelSylt
{
	class CSubscriptions
	{
	public:
		CSubscriptions();
		~CSubscriptions();
		void AddSubscription(const SSubscriptionHandle& InHandle);
	private:
		std::vector<SSubscriptionHandle> Handles;

	};
}

namespace SS = SpelSylt;