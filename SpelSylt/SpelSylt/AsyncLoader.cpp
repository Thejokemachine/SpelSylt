#include "SpelSyltPCH.h"

#include "Assets.h"
#include "AsyncLoader.h"
#include "FileLoader.h"

//------------------------------------------------------------------

CAsyncLoader::CAsyncLoader()
	: LoadQueue()
	, HaveStopRequest(false)
	, IsStopped(false)
{
}

//------------------------------------------------------------------

void CAsyncLoader::ProvideThread(std::thread& InThread)
{
	InThread = std::thread([&]() {StartTicking(); });
}

//------------------------------------------------------------------

void CAsyncLoader::RequestShutDown()
{
	HaveStopRequest = true;
}

//------------------------------------------------------------------

bool CAsyncLoader::HasShutDown() const
{
	return IsStopped;
}

//------------------------------------------------------------------

void CAsyncLoader::LoadAsync(const char* InPath, SBaseAsset& InTo)
{
	InTo.LoadStatus = ELoadRequestStatus::Pending;
	LoadQueue.push({InPath, InTo});
}

//------------------------------------------------------------------

void CAsyncLoader::StartTicking()
{
	while (!HaveStopRequest)
	{
		if (LoadQueue.empty())
		{
			std::this_thread::yield();
			continue;
		}

		DoLoad(LoadQueue.front());
		LoadQueue.pop();
	}

	IsStopped = true;
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