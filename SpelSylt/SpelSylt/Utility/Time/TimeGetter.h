#pragma once


namespace SpelSylt
{
	struct SDateTime;

	class ITimeGetter
	{
	public:
		virtual float GetDeltaTime() = 0;
		virtual float GetTotalTime() = 0;

		virtual void GetNowAsDateTime(SDateTime& OutDateTime) const = 0;
	};
}

namespace SS = SpelSylt;