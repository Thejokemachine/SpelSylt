#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/Utility/Async/SpelSyltThread.h"

using namespace SpelSylt;

//------------------------------------------------------------------

CSSThread::CSSThread()
	: StopRequested(false)
	, IsStopped(false)
	, Thread()
	, WorkerList()
	, WorkerStorage(1000)
	, NextWorkerIndex(0)
{
}

//------------------------------------------------------------------

CSSThread::~CSSThread()
{
	Thread.join();

	for (CAsyncWorker*& Worker : WorkerList)
	{
		delete Worker;
		Worker = nullptr;
	}
}

//------------------------------------------------------------------

void CSSThread::Start()
{
	Thread = std::thread([&] { Run(); });
}

//------------------------------------------------------------------

void CSSThread::RequestStop()
{
	StopRequested = true;
}

//------------------------------------------------------------------

bool CSSThread::HaveStopped() const
{
	return IsStopped;
}

//------------------------------------------------------------------

void CSSThread::Run()
{
	while (!StopRequested)
	{
		CAsyncWorker& CurrentWorker = *WorkerList[NextWorkerIndex];

		if (CurrentWorker.ShouldWork())
		{
			CurrentWorker.DoWork();
			CurrentWorker.EndWork();
		}

		NextWorkerIndex++;
		NextWorkerIndex %= WorkerList.size();
	}

	IsStopped = true;
}

//------------------------------------------------------------------