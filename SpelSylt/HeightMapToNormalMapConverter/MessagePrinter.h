#pragma once
#include <iostream>
#include <string>

namespace MessagePrinter
{
	static void PrintError(const std::string& InMessage)
	{
		std::cout << "[ERROR]" << InMessage << std::endl;
	}

	static void PrintMessage(const std::string& InMessage)
	{
		std::cout << "[Message]" << InMessage << std::endl;
	}

	static void PrintNumberedMessage(const unsigned int InNumber, const std::string& InMessage)
	{
		std::cout << "[" << InNumber << "]" << InMessage << std::endl;
	}
}