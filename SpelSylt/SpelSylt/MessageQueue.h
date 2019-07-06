#pragma once

#include "BaseEvent.h"

#include <queue>
#include <unordered_map>
#include <utility>
#include <functional>

#include "EventSubscriberList.h"
#include "EventSubscriberListInterface.h"

class CMessageQueue
{
public:
	template<typename EventType>
	void Subscribe(std::function<void(const EventType&)> InCallback);

	template<typename EventType, typename ... Params>
	void DispatchEvent(Params... InParams);
	
	void SendAllEvents();
private:
	bool ContainsSubscriberListOfType(size_t InTypeHash) const;

	template<typename EventType>
	void CreateSubscriberList();

	template<typename EventType>
	size_t GetEventHash() const;

	std::queue<SBaseEvent*> EventQueue;
	std::unordered_map<size_t, IEventSubscriberList*> PerEventSubscribers;
};

//------------------------------------------------------------------
//BEGIN IMPL
//------------------------------------------------------------------

template<typename EventType>
inline void CMessageQueue::Subscribe(std::function<void(const EventType&)> InCallback)
{
	static_assert(std::is_base_of<SBaseEvent, EventType>(), "Subscribing only allowed to events");

	const size_t EventHash = GetEventHash<EventType>();
	if (!ContainsSubscriberListOfType(EventHash))
	{
		CreateSubscriberList<EventType>();
	}

	reinterpret_cast<TEventSubscriberList<EventType>*>(PerEventSubscribers[EventHash])->AddSubscriber(InCallback);
}

//------------------------------------------------------------------

template<typename EventType, typename ...Params>
inline void CMessageQueue::DispatchEvent(Params ...InParams)
{
	static_assert(std::is_base_of<SBaseEvent, EventType>(), "Dispatching only allowed of events");
	EventQueue.push(new EventType(InParams...));
	EventQueue.back()->SetEventHash(GetEventHash<EventType>());
}

//------------------------------------------------------------------

template<typename EventType>
inline void CMessageQueue::CreateSubscriberList()
{
	const size_t EventHash = GetEventHash<EventType>();
	PerEventSubscribers[EventHash] = new TEventSubscriberList<EventType>();
}

//------------------------------------------------------------------

template<typename EventType>
inline size_t CMessageQueue::GetEventHash() const
{
	return typeid(EventType).hash_code();
}

//------------------------------------------------------------------
//END IMPL
//------------------------------------------------------------------
