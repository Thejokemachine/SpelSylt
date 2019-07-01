#pragma once
#include "AsyncOperationInterface.h"
#include "AsyncLoaderInterface.h"

#include "MemAllocSizes.h"

#include "LoadRequestTicket.h"

#include <atomic>
#include <queue>
#include <list>
#include <string>
#include <unordered_map>

struct SLoadHandle
{
	SLoadHandle()
		: Path("")
		, ID(0)
		, DataStart(nullptr)
		, DataSize()
	{}

	SLoadHandle(const char* InPath, unsigned int InID)
		: Path(InPath)
		, ID(InID)
		, DataStart(nullptr)
		, DataSize()
	{}

	void Destroy()
	{
		delete[DataSize] DataStart;
	}

	std::string Path;
	unsigned int ID;
	void* DataStart;
	B DataSize;
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
	virtual const SLoadRequestTicket* LoadAsync(const char* InPath) override;
	virtual void HandInTicket(const SLoadRequestTicket*& InTicket, void* OutDataLocation) override;
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