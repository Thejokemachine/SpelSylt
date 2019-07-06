#include "SpelSyltPCH.h"

#include "MessageQueue.h"

//------------------------------------------------------------------

void CMessageQueue::SendAllEvents()
{
	while (!EventQueue.empty())
	{
		SBaseEvent* Event = EventQueue.front();
		if (ContainsSubscriberListOfType(Event->GetEventHash()))
		{
			PerEventSubscribers[Event->GetEventHash()]->DispatchToAllSubscribers(Event);
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