#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/Utility/Time/Time.h"
#include "SpelSylt/Utility/Time/DateTime.h"
#include <ctime>
#include <iomanip>

using namespace SpelSylt;

SS::CTime::CTime()
	: myDeltaTime()
	, myTotalTime()
{
}


SS::CTime::~CTime()
{
}

void SS::CTime::Init()
{
	myStartingTimePoint = std::chrono::high_resolution_clock::now();
}

void SS::CTime::Update()
{
	myLastTimePoint = myCurrentTimePoint;

	myCurrentTimePoint = std::chrono::high_resolution_clock::now();

	myDeltaTime = myCurrentTimePoint - myLastTimePoint;
	myTotalTime = myCurrentTimePoint - myStartingTimePoint;
}

float SS::CTime::GetDeltaTime()
{
	return myDeltaTime.count();
}

float SS::CTime::GetTotalTime()
{
	return myTotalTime.count();
}

void SS::CTime::GetNowAsDateTime(SS::SDateTime& OutDateTime) const
{
	std::time_t TimeTNow = std::time(0);
	std::tm LocalTime;// = std::localtime(&TimeTNow);
	localtime_s(&LocalTime, &TimeTNow);

	OutDateTime.Day = LocalTime.tm_mday;
	OutDateTime.Month = LocalTime.tm_mon + 1; //Compensate for the fact that this is "months SINCE january"
	OutDateTime.Year = LocalTime.tm_year + 1900; //tm_year returns years SINCE 1900 so to get current year we add 1900
	OutDateTime.Hour = LocalTime.tm_hour;
	OutDateTime.Minute = LocalTime.tm_min;
	OutDateTime.Second = LocalTime.tm_sec;
}