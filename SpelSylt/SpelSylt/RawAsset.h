#pragma once

#include "MemAllocSizes.h"

struct SRawAsset
{
	SRawAsset()
		: DataLocation(nullptr)
		, DataSize()
	{}

	SRawAsset(char* InDataLocation, B InDataSize)
		: DataLocation(InDataLocation)
		, DataSize(InDataSize)
	{
	}

	~SRawAsset()
	{
		delete[DataSize] DataLocation;
	}

	char* DataLocation;
	B DataSize;
};