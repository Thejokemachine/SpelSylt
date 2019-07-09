#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/Debugging/Logging/DebugLogger.h"

#include "SpelSylt/Utility/Time/Time.h"
#include "SpelSylt/Utility/Time/DateTime.h"
#include "SpelSylt/FileHandling/DirectoryHelpers.h"
#include "SpelSylt/FileHandling/TextFileHandler.h"

#include <cstdarg>
#include <windows.h>
#include <string>
#include <sstream>

//------------------------------------------------------------------

CDebugLogger::CDebugLogger()
	: ShouldLogToFile(false)
	, LogFileName("")
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

	//This code builds a string with the va_args included for easier forwarding to the functions later printing the log to cmd or file
	va_start(Args, InLogMessage);
	LogLength += vsnprintf(NULL, 0, InLogMessage, Args);
	va_end(Args);

	LogMessage = (char*)calloc(LogLength + 1, sizeof(char));

	va_start(Args, InLogMessage);
	vsnprintf(LogMessage, LogLength + 1, InLogMessage, Args);
	va_end(Args);

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

	std::string LogLevelStr;
	VerbosityLevelToString(InLogLevel, LogLevelStr);

	printf_s(LogLevelStr.c_str());
	printf_s(InLogCat);
	printf_s(": ");
	printf_s(InLogMessage);
	printf_s("\n");
}

//------------------------------------------------------------------

void CDebugLogger::PrintToFile(LogLevels::ELogLevel InLogLevel, const char* InLogCat, const char* InLogMessage)
{
	std::string LogLevelName = "";
	VerbosityLevelToString(InLogLevel, LogLevelName);
	
	std::stringstream FullLogMessage;
	FullLogMessage << LogLevelName << "[Category: " << InLogCat << "] " << InLogMessage;

	LogFileHandler.OpenFile(LogFileName, CTextFileHandler::EFileOpenMode::Write);
	LogFileHandler.WriteLine(FullLogMessage.str());
	LogFileHandler.CloseFile();
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

	//Construct temporary Time only for Date
	//Note: This is not initialized and should not be used for any operations that require it to be
	const CTime Time; 

	MakeLogFileName(Time);

	//TODO: This is very clunky?
	SDateTime CurrentDateTime;
	Time.GetNowAsDateTime(CurrentDateTime);
	std::string CurrentDateTimeStr;
	CurrentDateTime.ToString(CurrentDateTimeStr);

	LogFileHandler.OpenFile(LogFileName, CTextFileHandler::EFileOpenMode::Write);
	LogFileHandler.Write("Logging session started: ");
	LogFileHandler.WriteLine(CurrentDateTimeStr);
	LogFileHandler.CloseFile();
}

//------------------------------------------------------------------

void CDebugLogger::BindDefaultColors()
{
	BindColorToLogLevel(LogLevels::ELogLevel::Verbose, ETextColor::Blue);
	BindColorToLogLevel(LogLevels::ELogLevel::Log, ETextColor::White);
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

void CDebugLogger::MakeLogFileName(const CTime& InTime)
{
	SDirectoryHelpers::CreateDirectoryIfNotExisting("DebugLogs/");

	SDateTime DateTime;
	InTime.GetNowAsDateTime(DateTime);
	std::string DateTimeStr;
	DateTime.ToString(DateTimeStr);

	LogFileName = "DebugLogs/SessionLog ";
	LogFileName += DateTimeStr;
	LogFileName += ".log";
}

//------------------------------------------------------------------

void CDebugLogger::VerbosityLevelToString(const LogLevels::ELogLevel InLogLevel, std::string& OutString) const
{
	switch (InLogLevel)
	{
	case LogLevels::ELogLevel::Verbose:
		OutString = "[VERBOSE]";
		break;
	case LogLevels::ELogLevel::Log:
		OutString = "[LOG]";
		break;
	case LogLevels::ELogLevel::Warning:
		OutString = "[WARNING]";
		break;
	case LogLevels::ELogLevel::Error:
		OutString = "[ERROR]";
		break;
	default:
		break;
	}
}

//------------------------------------------------------------------