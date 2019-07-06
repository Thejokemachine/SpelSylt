#pragma once

#include "EventSubscriberListInterface.h"

#include <vector>
#include <functional>

template<typename EventType>
class TEventSubscriberList final
	: public IEventSubscriberList
{
public:
	void AddSubscriber(std::function<void(const EventType&)> InCallback);
	virtual void DispatchToAllSubscribers(const SBaseEvent* InEvent) override;
private:
	using FSubscriberList = std::vector<std::function<void(const EventType&)>>;
	FSubscriberList SubscriberList;
};

//------------------------------------------------------------------
//BEGIN IMPL
//------------------------------------------------------------------

template<typename EventType>
inline void TEventSubscriberList<EventType>::AddSubscriber(std::function<void(const EventType&)> InCallback)
{
	SubscriberList.push_back(InCallback);
}

//------------------------------------------------------------------

template<typename EventType>
inline void TEventSubscriberList<EventType>::DispatchToAllSubscribers(const SBaseEvent* InEvent)
{
	const EventType* TrueEvent = reinterpret_cast<const EventType*>(InEvent);

	for (const auto& SubscriberCallback : SubscriberList)
	{
		SubscriberCallback(*TrueEvent);
	}
}

//------------------------------------------------------------------
//END IMPL
//------------------------------------------------------------------

