#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/Utility/Async/AsyncWorker.h"

using namespace SpelSylt;

//------------------------------------------------------------------

CAsyncWorker::CAsyncWorker()
	: LastWorkFinishedTime()
	, WorkInterval(std::chrono::milliseconds(0))
{
}

//------------------------------------------------------------------

bool CAsyncWorker::ShouldWork() const
{
	FWorkTime CurrentTime = std::chrono::high_resolution_clock::now();
	std::chrono::milliseconds TimeSinceLastWorkFinished = std::chrono::duration_cast<std::chrono::milliseconds>( CurrentTime - LastWorkFinishedTime);

	return TimeSinceLastWorkFinished >= WorkInterval;
}

//------------------------------------------------------------------

void CAsyncWorker::DoWork()
{
	LOG_WARNING(AsyncWorker, "Pure async worker detected. No work performed");
}

//------------------------------------------------------------------

void CAsyncWorker::EndWork()
{
	LastWorkFinishedTime = std::chrono::high_resolution_clock::now();
}

//------------------------------------------------------------------

void CAsyncWorker::SetWorkInterval(FWorkInterval& InInterval)
{
	WorkInterval = InInterval;
}

//------------------------------------------------------------------
