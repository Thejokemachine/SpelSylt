#include "SpelSyltPCH.h"
#include "UI/UIUtilities.h"
#include "Math/CommonMath.h"
#include "UI/Panel.h"

using namespace UI;

std::vector<std::string> UIUtilities::SplitString(const std::string & aString, const char aDelim)
{
	std::vector<std::string> strings;

	std::string s;
	for (char c : aString)
	{
		if (c == aDelim)
		{
			strings.push_back(s);
			s.clear();
		}
		else
		{
			s.push_back(c);
		}
	}
	if (!s.empty())
		strings.push_back(s);

	return strings;
}

int UIUtilities::HexToInt(const std::string& aHexNumber)
{
	auto evaluateChar = [](char c) {
		int rv = c - 48;
		if (c == 'a' || c == 'A')
			rv = 10;
		if (c == 'b' || c == 'B')
			rv = 11;
		if (c == 'c' || c == 'C')
			rv = 12;
		if (c == 'd' || c == 'D')
			rv = 13;
		if (c == 'e' || c == 'E')
			rv = 14;
		if (c == 'f' || c == 'F')
			rv = 15;
		return rv;
	};

	int first = evaluateChar(aHexNumber[0]);
	int second = evaluateChar(aHexNumber[1]);

	return (first << 4) + second;
}

unsigned char UIUtilities::EvaluateDockingFlags(const std::string & aBlock)
{
	unsigned char flags = 0;

	if (aBlock.empty())
		return flags;

	if (aBlock.find("left") != std::string::npos)
		flags |= DockFlag::Left;
	if (aBlock.find("right") != std::string::npos)
		flags |= DockFlag::Right;
	if (aBlock.find("top") != std::string::npos)
		flags |= DockFlag::Top;
	if (aBlock.find("bottom") != std::string::npos)
		flags |= DockFlag::Bottom;
	if (aBlock.find("center") != std::string::npos)
	{
		if (aBlock.find("hcenter") != std::string::npos)
			flags |= DockFlag::HCenter;
		if (aBlock.find("vcenter") != std::string::npos)
			flags |= DockFlag::VCenter;
		if ((!(flags & DockFlag::VCenter) && !(flags & DockFlag::HCenter)))
			flags |= DockFlag::Center;
	}

	return flags;
}

sf::Color UIUtilities::EvaluateColor(const std::string & aBlock)
{
	sf::Color rv = sf::Color::White;

	if (aBlock.empty())
		return rv;

	bool isHex = aBlock[0] == '#';
	if (isHex)
	{
		std::string block(++aBlock.begin(), aBlock.end());
		rv.r = Math::Clamp(UIUtilities::HexToInt(std::string(1, block[0]) + std::string(1, block[1])), 0, 255);
		rv.g = Math::Clamp(UIUtilities::HexToInt(std::string(1, block[2]) + std::string(1, block[3])), 0, 255);
		rv.b = Math::Clamp(UIUtilities::HexToInt(std::string(1, block[4]) + std::string(1, block[5])), 0, 255);
		if (block.size() == 8)
			rv.a = Math::Clamp(UIUtilities::HexToInt(std::string(1, block[6]) + std::string(1, block[7])), 0, 255);
	}
	else
	{
		auto values = UIUtilities::SplitString(aBlock, ',');
		rv.r = Math::Clamp(std::stoi(values[0]), 0, 255);
		rv.g = Math::Clamp(std::stoi(values[1]), 0, 255);
		rv.b = Math::Clamp(std::stoi(values[2]), 0, 255);
		if (values.size() == 4)
			rv.a = Math::Clamp(std::stoi(values[3]), 0, 255);
	}
	return rv;
}