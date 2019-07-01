#pragma once
#include "LoadEnums.h"

#include <atomic>

using FRequestID = unsigned int;

struct SLoadRequestTicket
{
	friend class CAsyncLoader;

public:
	std::atomic<ELoadRequestStatus> Status;
	FRequestID ID;
private:
	void operator=(const SLoadRequestTicket& InRHS)
	{
		Status = InRHS.Status.load();
		ID = InRHS.ID;
	}
};