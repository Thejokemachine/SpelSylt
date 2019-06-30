#pragma once

struct SDateTime;

class ITimeGetter
{
public:
	virtual float GetDeltaTime() = 0;
	virtual float GetTotalTime() = 0;

	virtual void GetNowAsDateTime(SDateTime& OutDateTime) const = 0;
};