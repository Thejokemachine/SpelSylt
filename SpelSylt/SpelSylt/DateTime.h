#pragma once
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