#include "SpelSyltPCH.h"

#include "MessageQueue.h"

//------------------------------------------------------------------

void CMessageQueue::Unsubscribe(const SSubscriptionHandle& InHandle)
{
	if (ContainsSubscriberListOfType(InHandle.GetMessageType()))
	{
		PerEventSubscribers[InHandle.GetMessageType()]->Unsubscribe(InHandle);
	}
}

//------------------------------------------------------------------

void CMessageQueue::SendAllEvents()
{
	while (!EventQueue.empty())
	{
		SBaseMessage* Event = EventQueue.front();
		if (ContainsSubscriberListOfType(Event->GetMessageHash()))
		{
			PerEventSubscribers[Event->GetMessageHash()]->DispatchToAllSubscribers(Event);
		}
		delete Event;
		EventQueue.pop();
	}
}

//------------------------------------------------------------------

bool CMessageQueue::ContainsSubscriberListOfType(size_t InTypeHash) const
{
	const auto& NotFound = PerEventSubscribers.end();
	return (PerEventSubscribers.find(InTypeHash) != NotFound);
}