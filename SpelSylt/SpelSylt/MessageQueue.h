#pragma once

#include "BaseEvent.h"

#include <queue>
#include <unordered_map>
#include <utility>
#include <functional>

#include "MessageSubscriberList.h"
#include "MessageSubscriberListInterface.h"
#include "Subscriptions.h"
#include "SubscriptionHandle.h"

class CMessageQueue
{
public:
	template<typename EventType>
	void Subscribe(std::function<void(const EventType&)> InCallback, CSubscriptions& InSubscriptions);
	
	void Unsubscribe(const SSubscriptionHandle& InHandle);

	template<typename EventType, typename ... Params>
	void DispatchEvent(Params... InParams);
	
	void SendAllEvents();
private:
	bool ContainsSubscriberListOfType(size_t InTypeHash) const;

	template<typename EventType>
	void CreateSubscriberList();

	template<typename EventType>
	size_t GetMessageHash() const;

	std::queue<SBaseEvent*> EventQueue;
	std::unordered_map<size_t, IMessageSubscriberList*> PerEventSubscribers;
};

//------------------------------------------------------------------
//BEGIN IMPL
//------------------------------------------------------------------

template<typename EventType>
inline void CMessageQueue::Subscribe(std::function<void(const EventType&)> InCallback, CSubscriptions& InSubscriptions)
{
	static_assert(std::is_base_of<SBaseEvent, EventType>(), "Subscribing only allowed to events");

	const size_t MessageHash = GetMessageHash<EventType>();
	if (!ContainsSubscriberListOfType(MessageHash))
	{
		CreateSubscriberList<EventType>();
	}

	TMessageSubscriberList<EventType>* SubscriberList = reinterpret_cast<TMessageSubscriberList<EventType>*>(PerEventSubscribers[MessageHash]);
	const size_t Identifier = SubscriberList->AddSubscriber(InCallback);

	SSubscriptionHandle CreatedHandle(Identifier, MessageHash, this);
	InSubscriptions.AddSubscription(CreatedHandle);
}

//------------------------------------------------------------------

template<typename EventType, typename ...Params>
inline void CMessageQueue::DispatchEvent(Params ...InParams)
{
	static_assert(std::is_base_of<SBaseEvent, EventType>(), "Dispatching only allowed of events");
	EventQueue.push(new EventType(InParams...));
	EventQueue.back()->SetMessageHash(GetMessageHash<EventType>());
}

//------------------------------------------------------------------

template<typename EventType>
inline void CMessageQueue::CreateSubscriberList()
{
	const size_t MessageHash = GetMessageHash<EventType>();
	PerEventSubscribers[MessageHash] = new TMessageSubscriberList<EventType>();
}

//------------------------------------------------------------------

template<typename EventType>
inline size_t CMessageQueue::GetMessageHash() const
{
	return typeid(EventType).hash_code();
}

//------------------------------------------------------------------
//END IMPL
//------------------------------------------------------------------
