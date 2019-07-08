#pragma once
#include "Utility/Async/AsyncOperationInterface.h"
#include "FileHandling/Loading/AsyncLoaderInterface.h"

#include "Memory/MemAllocSizes.h"

#include "FileHandling/Asset/Assets.h"
#include <atomic>
#include <queue>
#include <list>
#include <string>
#include <unordered_map>

struct SLoadHandle
{
	SLoadHandle()
		: Path("")
		, RawAsset(nullptr)
	{}

	SLoadHandle(const char* InPath, SBaseAsset& InRawAsset)
		: Path(InPath)
		, RawAsset(&InRawAsset)
	{}

	std::string Path;
	SBaseAsset* RawAsset;
};

class CAsyncLoader final
	: public IAsyncOperation
	, public IAsyncLoader
{
public:
	CAsyncLoader();

	//Begin IAsyncOperation
	virtual void ProvideThread(std::thread& InThread) override;
	virtual void RequestShutDown() override;
	virtual bool HasShutDown() const override;
	//End IAsyncOperation

	//Begin IAsyncLoader
	virtual void LoadAsync(const char* InPath, SBaseAsset& InTo) override;
	//End IAsyncLoader
private:
	void StartTicking();
	void DoLoad(SLoadHandle& InLoadHandle);
	
	using FLoadQueue = std::queue<SLoadHandle, std::list<SLoadHandle>>;
	FLoadQueue LoadQueue;

	std::atomic_bool HaveStopRequest;
	std::atomic_bool IsStopped;
};