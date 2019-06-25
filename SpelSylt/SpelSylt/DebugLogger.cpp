#include "DebugLogger.h"

#include <cstdarg>
#include <windows.h>

//------------------------------------------------------------------

CDebugLogger::CDebugLogger()
{
	BindDefaultColors();
	SetLogLevel(ELogLevel::Verbose);
}

//------------------------------------------------------------------

CDebugLogger& CDebugLogger::GetInstance()
{
	static CDebugLogger Instance;
	return Instance;
}

//------------------------------------------------------------------

void CDebugLogger::PrintLog(ELogLevel InLogLevel, const char* InLogCat, const char* InLogMessage, ...)
{
	if (!CurrentLogLevelAllowsRequestedLogLevel(InLogLevel))
	{
		return;
	}

	SetTextColor(LogColorMap[InLogLevel]);

	printf_s(InLogCat);
	printf_s(": ");

	va_list Args;
	va_start(Args, InLogMessage);
	vprintf_s(InLogMessage, Args);
	va_end(Args);

	printf_s("\n");
}

//------------------------------------------------------------------

void CDebugLogger::SetLogLevel(ELogLevel InLogLevel)
{
	CurrentLogLevel = InLogLevel;
}

//------------------------------------------------------------------

void CDebugLogger::BindColorToLogLevel(ELogLevel InLogLevel, ETextColor InColor)
{
	LogColorMap[InLogLevel] = InColor;
}

//------------------------------------------------------------------

void CDebugLogger::BindDefaultColors()
{
	BindColorToLogLevel(ELogLevel::Verbose, ETextColor::Blue);
	BindColorToLogLevel(ELogLevel::Log, ETextColor::Green);
	BindColorToLogLevel(ELogLevel::Warning, ETextColor::Yellow);
	BindColorToLogLevel(ELogLevel::Error, ETextColor::Red);
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

bool CDebugLogger::CurrentLogLevelAllowsRequestedLogLevel(ELogLevel InRequestedLogLevel) const
{
	const auto RequestedAsInt = static_cast<unsigned int>(InRequestedLogLevel);
	const auto CurrentAsInt = static_cast<unsigned int>(CurrentLogLevel);

	return RequestedAsInt >= CurrentAsInt;
}

//------------------------------------------------------------------