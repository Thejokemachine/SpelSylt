#include "DebugLogger.h"
#include <cstdarg>

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
}

//------------------------------------------------------------------