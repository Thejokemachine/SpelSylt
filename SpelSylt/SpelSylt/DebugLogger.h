#pragma once
#include <unordered_map>

//------------------------------------------------------------------

/*
Note: All Logging should be done through these macros

Exceptions are when rebinding colors
*/

#define SET_LOG_LEVEL_VERBOSE					CDebugLogger::GetInstance().SetLogLevel(CDebugLogger::ELogLevel::Verbose)
#define SET_LOG_LEVEL_LOG						CDebugLogger::GetInstance().SetLogLevel(CDebugLogger::ELogLevel::Log)
#define SET_LOG_LEVEL_WARNING					CDebugLogger::GetInstance().SetLogLevel(CDebugLogger::ELogLevel::Warning)
#define SET_LOG_LEVEL_ERROR						CDebugLogger::GetInstance().SetLogLevel(CDebugLogger::ELogLevel::Error)

#define LOG_VERBOSE(LogCat, LogMessage, ...)	CDebugLogger::GetInstance().PrintLog(CDebugLogger::ELogLevel::Verbose, #LogCat, LogMessage, __VA_ARGS__)
#define LOG_LOG(LogCat, LogMessage, ...)		CDebugLogger::GetInstance().PrintLog(CDebugLogger::ELogLevel::Log, #LogCat, LogMessage, __VA_ARGS__)
#define LOG_WARNING(LogCat, LogMessage, ...)	CDebugLogger::GetInstance().PrintLog(CDebugLogger::ELogLevel::Warning, #LogCat, LogMessage, __VA_ARGS__)
#define LOG_ERROR(LogCat, LogMessage, ...)		CDebugLogger::GetInstance().PrintLog(CDebugLogger::ELogLevel::Error, #LogCat, LogMessage, __VA_ARGS__)

//------------------------------------------------------------------

class CDebugLogger
{
public:
	enum class ETextColor
	{
		Green,
		Blue,
		Yellow,
		Red,
		White,
	};

	enum class ELogLevel
	{
		Verbose,
		Log,
		Warning,
		Error,
	};

public:
	static CDebugLogger& GetInstance();

	void PrintLog(ELogLevel InLogLevel, const char* InLogCat, const char* InLogMessage, ...);

	void SetLogLevel(ELogLevel InLogLevel);

	void BindColorToLogLevel(ELogLevel InLogLevel, ETextColor InColor);

private:
	using FLogColorMap = std::unordered_map<ELogLevel, ETextColor>;
	
	CDebugLogger();

	void BindDefaultColors();
	void SetTextColor(ETextColor InColor);

	FLogColorMap LogColorMap;
	ELogLevel CurrentLogLevel;
};

//------------------------------------------------------------------