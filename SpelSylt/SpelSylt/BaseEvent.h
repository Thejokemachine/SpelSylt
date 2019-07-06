#pragma once

struct SBaseEvent
{
	void SetMessageHash(size_t InEventHash)
	{
		EventHash = InEventHash;
	}

	size_t GetMessageHash() const
	{
		return EventHash;
	}

private:
	size_t EventHash;
};