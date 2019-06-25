#include "DebugLogger.h"

#include <cstdarg>
#include <windows.h>
#include <string>
#include <fstream>
#include <ctime>

//------------------------------------------------------------------

CDebugLogger::CDebugLogger()
	: ShouldLogToFile(false)
{
	BindDefaultColors();
	SetLogLevel(LogLevels::ELogLevel::Verbose);
}

//------------------------------------------------------------------

CDebugLogger& CDebugLogger::GetInstance()
{
	static CDebugLogger Instance;
	return Instance;
}

//------------------------------------------------------------------

void CDebugLogger::PrintLog(LogLevels::ELogLevel InLogLevel, const char* InLogCat, const char* InLogMessage, ...)
{
	if (!CurrentLogLevelAllowsRequestedLogLevel(InLogLevel))
	{
		return;
	}

	va_list Args;
	int LogLength = 0;
	char* LogMessage;

	//EXPERIMENTAL
	va_start(Args, InLogMessage);
	LogLength += vsnprintf(NULL, 0, InLogMessage, Args);
	va_end(Args);

	LogMessage = (char*)calloc(LogLength + 1, sizeof(char));

	va_start(Args, InLogMessage);
	vsnprintf(LogMessage, LogLength + 1, InLogMessage, Args);
	va_end(Args);
	//END EXPERIMENTAL

	PrintToConsole(InLogLevel, InLogCat, LogMessage);
	if (ShouldLogToFile)
	{
		PrintToFile(InLogLevel, InLogCat, LogMessage);
	}

	free(LogMessage);
}

//------------------------------------------------------------------

void CDebugLogger::PrintToConsole(LogLevels::ELogLevel InLogLevel, const char* InLogCat, const char* InLogMessage)
{
	SetTextColor(LogColorMap[InLogLevel]);
	printf_s(InLogCat);
	printf_s(": ");
	printf_s(InLogMessage);
	printf_s("\n");
}

//------------------------------------------------------------------

void CDebugLogger::PrintToFile(LogLevels::ELogLevel InLogLevel, const char* InLogCat, const char* InLogMessage)
{
	const char* LogLevelName = "";

	switch (InLogLevel)
	{
	case LogLevels::ELogLevel::Verbose:
		LogLevelName = "[VERBOSE]";
		break;
	case LogLevels::ELogLevel::Log:
		LogLevelName = "[LOG]";
		break;
	case LogLevels::ELogLevel::Warning:
		LogLevelName = "[WARNING]";
		break;
	case LogLevels::ELogLevel::Error:
		LogLevelName = "[ERROR]";
		break;
	default:
		break;
	}

	std::ofstream FileStream;
	FileStream.open("DebugLog.log", std::fstream::app);
	FileStream << LogLevelName;
	FileStream << "[Category: " << InLogCat << "] ";
	FileStream << InLogMessage << "\n";
	FileStream.close();
}

//------------------------------------------------------------------

void CDebugLogger::SetLogLevel(LogLevels::ELogLevel InLogLevel)
{
	CurrentLogLevel = InLogLevel;
}

//------------------------------------------------------------------

void CDebugLogger::BindColorToLogLevel(LogLevels::ELogLevel InLogLevel, ETextColor InColor)
{
	LogColorMap[InLogLevel] = InColor;
}

//------------------------------------------------------------------

void CDebugLogger::SetShouldLogToFile()
{
	ShouldLogToFile = true;

	std::ofstream LogFileStream;
	LogFileStream.open("DebugLog.log", std::ofstream::trunc);
	LogFileStream.close();
}

//------------------------------------------------------------------

void CDebugLogger::BindDefaultColors()
{
	BindColorToLogLevel(LogLevels::ELogLevel::Verbose, ETextColor::Blue);
	BindColorToLogLevel(LogLevels::ELogLevel::Log, ETextColor::Green);
	BindColorToLogLevel(LogLevels::ELogLevel::Warning, ETextColor::Yellow);
	BindColorToLogLevel(LogLevels::ELogLevel::Error, ETextColor::Red);
}

//------------------------------------------------------------------

void CDebugLogger::SetTextColor(ETextColor InColor)
{
	WORD Color = -1;
	
	switch (InColor)
	{
	case CDebugLogger::ETextColor::Green:
		Color = 10;
		break;
	case CDebugLogger::ETextColor::Blue:
		Color = 11;
		break;
	case CDebugLogger::ETextColor::Yellow:
		Color = 14;
		break;
	case CDebugLogger::ETextColor::Red:
		Color = 12;
		break;
	case CDebugLogger::ETextColor::White:
		Color = 7;
		break;
	default:
		break;
	}

	HANDLE CmdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(CmdHandle, Color);
}

//------------------------------------------------------------------

bool CDebugLogger::CurrentLogLevelAllowsRequestedLogLevel(LogLevels::ELogLevel InRequestedLogLevel) const
{
	const auto RequestedAsInt = static_cast<unsigned int>(InRequestedLogLevel);
	const auto CurrentAsInt = static_cast<unsigned int>(CurrentLogLevel);

	return RequestedAsInt >= CurrentAsInt;
}

//------------------------------------------------------------------