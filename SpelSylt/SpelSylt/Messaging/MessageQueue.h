#pragma once

#include "SpelSylt/Messaging/Messages/BaseMessage.h"

#include <queue>
#include <unordered_map>
#include <utility>
#include <functional>

#include "SpelSylt/Messaging/Subscribing/MessageSubscriberList.h"
#include "SpelSylt/Messaging/Subscribing/MessageSubscriberListInterface.h"
#include "SpelSylt/Messaging/Subscribing/Subscriptions.h"
#include "SpelSylt/Messaging/Subscribing/SubscriptionHandle.h"

namespace SpelSylt
{
	class CMessageQueue
	{
	public:
		template<typename MessageType>
		void Subscribe(std::function<void(const MessageType&)> InCallback, CSubscriptions& InSubscriptions);

		void Unsubscribe(const SSubscriptionHandle& InHandle);

		template<typename MessageType, typename ... Params>
		void DispatchEvent(Params... InParams);

		void SendAllEvents();
	private:
		bool ContainsSubscriberListOfType(size_t InTypeHash) const;

		template<typename MessageType>
		void CreateSubscriberList();

		template<typename MessageType>
		size_t GetMessageHash() const;

		std::queue<SBaseMessage*> EventQueue;
		std::unordered_map<size_t, IMessageSubscriberList*> PerEventSubscribers;
	};

	//------------------------------------------------------------------
	//BEGIN IMPL
	//------------------------------------------------------------------

	template<typename MessageType>
	inline void CMessageQueue::Subscribe(std::function<void(const MessageType&)> InCallback, CSubscriptions& InSubscriptions)
	{
		static_assert(std::is_base_of<SBaseMessage, MessageType>(), "Subscribing only allowed to events");

		const size_t MessageHash = GetMessageHash<MessageType>();
		if (!ContainsSubscriberListOfType(MessageHash))
		{
			CreateSubscriberList<MessageType>();
		}

		TMessageSubscriberList<MessageType>* SubscriberList = reinterpret_cast<TMessageSubscriberList<MessageType>*>(PerEventSubscribers[MessageHash]);
		const size_t Identifier = SubscriberList->AddSubscriber(InCallback);

		SSubscriptionHandle CreatedHandle(Identifier, MessageHash, this);
		InSubscriptions.AddSubscription(CreatedHandle);
	}

	//------------------------------------------------------------------

	template<typename MessageType, typename ...Params>
	inline void CMessageQueue::DispatchEvent(Params ...InParams)
	{
		static_assert(std::is_base_of<SBaseMessage, MessageType>(), "Dispatching only allowed of events");
		EventQueue.push(new MessageType(InParams...));
		EventQueue.back()->SetMessageHash(GetMessageHash<MessageType>());
	}

	//------------------------------------------------------------------

	template<typename MessageType>
	inline void CMessageQueue::CreateSubscriberList()
	{
		const size_t MessageHash = GetMessageHash<MessageType>();
		PerEventSubscribers[MessageHash] = new TMessageSubscriberList<MessageType>();
	}

	//------------------------------------------------------------------

	template<typename MessageType>
	inline size_t CMessageQueue::GetMessageHash() const
	{
		return typeid(MessageType).hash_code();
	}

	//------------------------------------------------------------------
	//END IMPL
	//------------------------------------------------------------------
}

namespace SS = SpelSylt;