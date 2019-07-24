#pragma once

#include "SpelSylt/Utility/Time/TimeGetter.h"

#include <chrono>
#include <string>

namespace SpelSylt
{
	struct SDateTime;

	class CTime
		: public ITimeGetter
	{
	public:
		CTime();
		~CTime();

		void Init();
		void Update();

		//Begin ITimeGetter
		virtual float GetDeltaTime() override;
		virtual float GetTotalTime() override;

		virtual void GetNowAsDateTime(SDateTime& OutDateTime) const override;
		//End ITimeGetter

		struct STimeData
		{
			float deltaTime;
			float totalTime;
			float trash[2];
		};

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> myLastTimePoint;
		std::chrono::time_point<std::chrono::high_resolution_clock> myCurrentTimePoint;
		std::chrono::time_point<std::chrono::high_resolution_clock> myStartingTimePoint;

		std::chrono::duration<float> myDeltaTime;
		std::chrono::duration<float> myTotalTime;
	};
}

namespace SS = SpelSylt;