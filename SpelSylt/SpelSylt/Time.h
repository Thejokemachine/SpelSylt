#pragma once
#include <chrono>
#include <string>

struct SDateTime
{
	unsigned char Day;
	unsigned char Month;
	unsigned short Year;
	unsigned char Hour;
	unsigned char Minute;
	unsigned char Second;

	void ToString(std::string& OutString)
	{
		//Make date
		OutString = std::to_string(Year);
		OutString += "-";
		OutString += std::to_string(Month);
		OutString += "-";
		OutString += std::to_string(Day);

		OutString += " ";

		OutString += std::to_string(Hour);
		OutString += "h";
		OutString += std::to_string(Minute);
		OutString += "m";
		OutString += std::to_string(Second);
		OutString += "s";
	}
};

class CTime
{
public:
	~CTime();
	
	static CTime& GetInstance();

	void Init();
	void Update();

	float GetDeltaTime();
	float GetTotalTime();

	void GetNowAsDateTime(SDateTime& OutDateTime) const;

	struct STimeData
	{
		float deltaTime;
		float totalTime;
		float trash[2];
	};

private:

	CTime();

	std::chrono::time_point<std::chrono::high_resolution_clock> myLastTimePoint;
	std::chrono::time_point<std::chrono::high_resolution_clock> myCurrentTimePoint;
	std::chrono::time_point<std::chrono::high_resolution_clock> myStartingTimePoint;

	std::chrono::duration<float> myDeltaTime;
	std::chrono::duration<float> myTotalTime;
};

