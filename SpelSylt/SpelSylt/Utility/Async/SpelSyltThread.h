#pragma once
#include <thread>
#include <atomic>
#include <vector>

#include "SpelSylt/Utility/Async/AsyncWorker.h"
#include "SpelSylt/Memory/Containers/StaticMemoryBuffer.h"

namespace SpelSylt
{
	class CSSThread
	{
	public:
		CSSThread();
		~CSSThread();
		CSSThread(const CSSThread&) = delete;

		template<typename TWorkerType, typename ...TEmplaceArgs>
		TWorkerType& EmplaceWorker(TEmplaceArgs...);

		void Start();
		void RequestStop();
		bool HaveStopped() const;
	private:
		void Run();

		using FWorkerList = std::vector<CAsyncWorker*>;
		
		std::atomic_bool StopRequested;
		std::atomic_bool IsStopped;

		std::thread Thread;
		FWorkerList WorkerList;
		CStaticMemoryBuffer WorkerStorage;

		unsigned int NextWorkerIndex;
	};
}

namespace SS = SpelSylt;

template<typename TWorkerType, typename ...TEmplaceArgs>
inline TWorkerType& SpelSylt::CSSThread::EmplaceWorker(TEmplaceArgs ... Args)
{
	TWorkerType& Worker = WorkerStorage.AddToBuffer<TWorkerType>(TWorkerType(Args...));
	WorkerList.push_back(&Worker);
	return Worker;
}