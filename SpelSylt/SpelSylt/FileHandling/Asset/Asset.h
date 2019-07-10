#pragma once

#include "SpelSylt/FileHandling/Loading/LoadEnums.h"
#include "SpelSylt/Memory/MemAllocSizes.h"

struct SBaseAsset
{
	friend class CAsyncLoader;

	SBaseAsset()
		: LoadStatus(ELoadRequestStatus::None)
	{}

	ELoadRequestStatus GetLoadStatus() const
	{
		return LoadStatus;
	}

protected:
	void SetData(char* InDataLocation, B InDataSize)
	{
		AssignData(InDataLocation, InDataSize);
	}

	virtual void AssignData(char* InDataLocation, B InDataSize) = 0;

private:
	ELoadRequestStatus LoadStatus;
};