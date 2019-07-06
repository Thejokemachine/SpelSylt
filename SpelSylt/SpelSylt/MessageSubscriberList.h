#pragma once

#include "MessageSubscriberListInterface.h"

#include <vector>
#include <functional>
#include "SubscriptionHandle.h"

template<typename EventType>
class TMessageSubscriberList final
	: public IMessageSubscriberList
{
public:
	TMessageSubscriberList();

	size_t AddSubscriber(std::function<void(const EventType&)> InCallback);
	
	//Begin IMessageSubscriberList
	virtual void Unsubscribe(const SSubscriptionHandle& InHandle) override;
	virtual void DispatchToAllSubscribers(const SBaseEvent* InEvent) override;
	//End IMessageSubscriberList

private:
	using FSubscriberData = std::pair<size_t, std::function<void(const EventType&)>>;
	using FSubscriberList = std::vector<FSubscriberData>;
	FSubscriberList SubscriberList;
	size_t NextIdentifier;
};

//------------------------------------------------------------------
//BEGIN IMPL
//------------------------------------------------------------------

template<typename EventType>
inline TMessageSubscriberList<EventType>::TMessageSubscriberList()
	: SubscriberList()
	, NextIdentifier(1)
{
}

//------------------------------------------------------------------

template<typename EventType>
size_t TMessageSubscriberList<EventType>::AddSubscriber(std::function<void(const EventType&)> InCallback)
{
	SubscriberList.push_back(FSubscriberData(NextIdentifier, InCallback));
	NextIdentifier++;

	return NextIdentifier - 1;
}

//------------------------------------------------------------------

template<typename EventType>
inline void TMessageSubscriberList<EventType>::Unsubscribe(const SSubscriptionHandle& InHandle)
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

template<typename EventType>
inline void TMessageSubscriberList<EventType>::DispatchToAllSubscribers(const SBaseEvent* InEvent)
{
	const EventType* TrueEvent = reinterpret_cast<const EventType*>(InEvent);

	for (const auto& Subscriber : SubscriberList)
	{
		Subscriber.second(*TrueEvent);
	}
}

//------------------------------------------------------------------
//END IMPL
//------------------------------------------------------------------

