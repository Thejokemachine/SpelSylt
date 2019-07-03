#pragma once
#include "AsyncOperationInterface.h"
#include "AsyncLoaderInterface.h"

#include "MemAllocSizes.h"

#include "LoadRequestTicket.h"
#include "Assets.h"
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
		, ID(0)
	{}

	SLoadHandle(const char* InPath, unsigned int InID, SBaseAsset& InRawAsset)
		: Path(InPath)
		, RawAsset(&InRawAsset)
		, ID(InID)
	{}

	std::string Path;
	SBaseAsset* RawAsset;
	unsigned int ID;
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
	virtual FLoadRequestTicket LoadAsync(const char* InPath, SBaseAsset& InTo) override;
	virtual void HandInTicket(FLoadRequestTicket& InTicket) override;
	//End IAsyncLoader
private:
	void StartTicking();
	void DoLoad(SLoadHandle& InLoadHandle);
	
	const SLoadRequestTicket& CreateNewTicket();
	void DestroyTicket(const SLoadRequestTicket& InTicket);

	using FLoadQueue = std::queue<SLoadHandle, std::list<SLoadHandle>>;
	FLoadQueue LoadQueue;

	using FInFlightLoadTickets = std::unordered_map<unsigned int, SLoadRequestTicket>;
	FInFlightLoadTickets InFlightLoadTickets;
	
	using FFinishedLoadHandles = std::unordered_map<unsigned int, SLoadHandle>;
	FFinishedLoadHandles FinishedLoadHandles;

	std::atomic_bool HaveStopRequest;
	std::atomic_bool IsStopped;

	unsigned int NextTicketID;
};