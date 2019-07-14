#pragma once

#include "SpelSylt/FileHandling/Loading/LoadEnums.h"
#include "SpelSylt/Memory/MemAllocSizes.h"

struct SBaseAsset
{
	SBaseAsset()
		: LoadStatus(ELoadRequestStatus::None)
	{}

	ELoadRequestStatus GetLoadStatus() const
	{
		return LoadStatus;
	}

	//These should probably be friended to the Loader for safety?
	void SetData(char* InDataLocation, B InDataSize)
	{
		AssignData(InDataLocation, InDataSize);
	}

	ELoadRequestStatus LoadStatus;
protected:
	virtual void AssignData(char* InDataLocation, B InDataSize) = 0;
};