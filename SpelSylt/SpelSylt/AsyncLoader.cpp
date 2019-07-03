#include "SpelSyltPCH.h"

#include "RawAsset.h"
#include "AsyncLoader.h"
#include "LoadRequestTicket.h"
#include "FileLoader.h"

#define NO_LOAD -1

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

const SLoadRequestTicket* CAsyncLoader::LoadAsync(const char* InPath)
{
	const SLoadRequestTicket& RequestTicket = CreateNewTicket();
	LoadQueue.push({InPath, RequestTicket.ID});
	return &RequestTicket;
}

//------------------------------------------------------------------

void CAsyncLoader::HandInTicket(FLoadRequestTicket& InTicket, SRawAsset& OutDataLocation)
{
	const SLoadRequestTicket& Ticket = *InTicket;

	if (Ticket.Status == ELoadRequestStatus::Done)
	{
		SLoadHandle& HandleForTicket = FinishedLoadHandles[Ticket.ID];
		
		//memcpy(OutDataLocation.DataLocation, HandleForTicket.DataStart, static_cast<unsigned long long>(HandleForTicket.DataSize));
		
		OutDataLocation.DataLocation = HandleForTicket.DataStart;
		OutDataLocation.DataSize = HandleForTicket.DataSize;
		
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
		InLoadHandle.DataSize = FileLoader.GetFileSize();
		
		char* LoadDataBuffer = new char[InLoadHandle.DataSize];
		InLoadHandle.DataStart = LoadDataBuffer;

		FileLoader.LoadData(InLoadHandle.DataStart);
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