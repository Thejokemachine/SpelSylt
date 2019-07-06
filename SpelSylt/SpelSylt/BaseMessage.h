#pragma once

struct SBaseMessage
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