#pragma once

#include "SpelSylt/Messaging/Subscribing/MessageSubscriberListInterface.h"

#include <vector>
#include <functional>
#include "SpelSylt/Messaging/Subscribing/SubscriptionHandle.h"

namespace SpelSylt
{

	template<typename MessageType>
	class TMessageSubscriberList final
		: public IMessageSubscriberList
	{
	public:
		TMessageSubscriberList();

		size_t AddSubscriber(std::function<void(const MessageType&)> InCallback);

		//Begin IMessageSubscriberList
		virtual void Unsubscribe(const SSubscriptionHandle& InHandle) override;
		virtual void DispatchToAllSubscribers(const SBaseMessage* InEvent) override;
		//End IMessageSubscriberList

	private:
		using FSubscriberData = std::pair<size_t, std::function<void(const MessageType&)>>;
		using FSubscriberList = std::vector<FSubscriberData>;
		FSubscriberList SubscriberList;
		size_t NextIdentifier;
	};
}


using namespace SpelSylt;

//------------------------------------------------------------------
//BEGIN IMPL
//------------------------------------------------------------------

template<typename MessageType>
inline TMessageSubscriberList<MessageType>::TMessageSubscriberList()
	: SubscriberList()
	, NextIdentifier(1)
{
}

//------------------------------------------------------------------

template<typename MessageType>
size_t TMessageSubscriberList<MessageType>::AddSubscriber(std::function<void(const MessageType&)> InCallback)
{
	SubscriberList.push_back(FSubscriberData(NextIdentifier, InCallback));
	NextIdentifier++;

	return NextIdentifier - 1;
}

//------------------------------------------------------------------

template<typename MessageType>
inline void TMessageSubscriberList<MessageType>::Unsubscribe(const SSubscriptionHandle& InHandle)
{
	int IndexToRemove = -1;
	for (int i = 0; i < SubscriberList.size(); ++i)
	{
		const FSubscriberData& CurrentData = SubscriberList[i];
		if (CurrentData.first == InHandle.GetIdentifier())
		{
			IndexToRemove = i;
			break;
		}
	}

	if (IndexToRemove >= 0)
	{
		SubscriberList.erase(SubscriberList.begin() + IndexToRemove);
	}
}

//------------------------------------------------------------------

template<typename MessageType>
inline void TMessageSubscriberList<MessageType>::DispatchToAllSubscribers(const SBaseMessage* InEvent)
{
	const MessageType* TrueEvent = reinterpret_cast<const MessageType*>(InEvent);

	for (const auto& Subscriber : SubscriberList)
	{
		Subscriber.second(*TrueEvent);
	}
}

//------------------------------------------------------------------
//END IMPL
//------------------------------------------------------------------

