#pragma once
#include <chrono>

namespace SpelSylt
{
	class CAsyncWorker
	{
	public:
		CAsyncWorker();
		bool ShouldWork() const;
		virtual void DoWork();
		void EndWork();
	protected:
		using FWorkInterval = std::chrono::milliseconds;

		void SetWorkInterval(FWorkInterval& InInterval);
	private:
		using FWorkTime = std::chrono::time_point<std::chrono::high_resolution_clock>;

		FWorkTime LastWorkFinishedTime;
		FWorkInterval WorkInterval;
	};
}

namespace SS = SpelSylt;