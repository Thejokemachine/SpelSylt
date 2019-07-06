#pragma once

struct SBaseEvent
{
	void SetEventHash(size_t InEventHash)
	{
		EventHash = InEventHash;
	}

	size_t GetEventHash() const
	{
		return EventHash;
	}

private:
	size_t EventHash;
};