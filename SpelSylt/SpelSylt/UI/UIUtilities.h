#pragma once
#include <string>
#include <vector>

namespace UIUtilities
{
	std::vector<std::string> SplitString(const std::string& aString, const char aDelim);
	std::string RemoveWhiteSpace(const std::string& aBlock);
	std::string FormatFloat(unsigned short aPrecision, float aNumber);

	int HexToInt(const std::string& aHexNumber);

	unsigned char EvaluateDockingFlags(const std::string& aBlock);
	sf::Color EvaluateColor(const std::string& aBlock);
}