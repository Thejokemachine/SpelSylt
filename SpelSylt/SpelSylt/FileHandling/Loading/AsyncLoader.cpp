#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/FileHandling/Asset/Assets.h"
#include "SpelSylt/FileHandling/Loading/AsyncLoader.h"
#include "SpelSylt/FileHandling/Loading/FileLoader.h"

//------------------------------------------------------------------

using namespace SpelSylt;

//------------------------------------------------------------------

CAsyncLoader::CAsyncLoader()
	: LoadQueue()
{
}

//------------------------------------------------------------------

void CAsyncLoader::LoadAsync(const char* InPath, SBaseAsset& InTo)
{
	InTo.LoadStatus = ELoadRequestStatus::Pending;
	LoadQueue.push_back({ InPath, InTo });
}

//------------------------------------------------------------------

void CAsyncLoader::DoWork()
{
	for (short i = 0; i < MaxAssetsToLoadPerCycle; ++i)
	{
		if (LoadQueue.empty())
		{
			break;
		}

		DoLoad(LoadQueue.front());
		LoadQueue.erase(LoadQueue.begin());
	}
}

//------------------------------------------------------------------

void CAsyncLoader::DoLoad(SLoadHandle& InLoadHandle)
{
	CFileLoader FileLoader(InLoadHandle.Path.c_str());
	if (FileLoader.IsValid())
	{
		//Create temporary buffer
		const B DataSize = FileLoader.GetFileSize();
		char* LoadDataBuffer = new char[DataSize];

		FileLoader.LoadData(LoadDataBuffer);
		InLoadHandle.RawAsset->SetData(LoadDataBuffer, DataSize);

		//Free allocated buffer
		delete[DataSize] LoadDataBuffer;
		InLoadHandle.RawAsset->LoadStatus = ELoadRequestStatus::Done;
	}
	else
	{
		InLoadHandle.RawAsset->LoadStatus = ELoadRequestStatus::Fail;
	}
}

//------------------------------------------------------------------