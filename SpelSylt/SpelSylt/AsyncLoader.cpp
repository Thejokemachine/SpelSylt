#include "SpelSyltPCH.h"

#include "Assets.h"
#include "AsyncLoader.h"
#include "LoadRequestTicket.h"
#include "FileLoader.h"

//------------------------------------------------------------------

CAsyncLoader::CAsyncLoader()
	: LoadQueue()
	, InFlightLoadTickets()
	, HaveStopRequest(false)
	, IsStopped(false)
	, NextTicketID(0)
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

const SLoadRequestTicket* CAsyncLoader::LoadAsync(const char* InPath, SBaseAsset& InTo)
{
	const SLoadRequestTicket& RequestTicket = CreateNewTicket();
	LoadQueue.push({InPath, RequestTicket.ID, InTo});
	return &RequestTicket;
}

//------------------------------------------------------------------

void CAsyncLoader::HandInTicket(FLoadRequestTicket& InTicket)
{
	const SLoadRequestTicket& Ticket = *InTicket;

	if (Ticket.Status == ELoadRequestStatus::Done)
	{
		SLoadHandle& HandleForTicket = FinishedLoadHandles[Ticket.ID];
		FinishedLoadHandles.erase(Ticket.ID);
	}

	DestroyTicket(Ticket);
	InTicket = nullptr;
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
	SLoadRequestTicket& TicketForLoaded = InFlightLoadTickets[InLoadHandle.ID];
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

		TicketForLoaded.Status = ELoadRequestStatus::Done;
		FinishedLoadHandles[InLoadHandle.ID] = InLoadHandle;
	}
	else
	{
		TicketForLoaded.Status = ELoadRequestStatus::Fail;
	}
}

//------------------------------------------------------------------

const SLoadRequestTicket& CAsyncLoader::CreateNewTicket()
{
	SLoadRequestTicket NewTicket;
	
	NewTicket.ID = NextTicketID;
	++NextTicketID;

	NewTicket.Status = ELoadRequestStatus::Pending;

	InFlightLoadTickets[NewTicket.ID] = NewTicket;

	return InFlightLoadTickets[NewTicket.ID];
}

//------------------------------------------------------------------

void CAsyncLoader::DestroyTicket(const SLoadRequestTicket& InTicket)
{
	InFlightLoadTickets.erase(InTicket.ID);
}

//------------------------------------------------------------------