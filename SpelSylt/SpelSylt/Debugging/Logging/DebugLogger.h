#pragma once

#include "SpelSylt/Debugging/Logging/LogLevels.h"
#include "SpelSylt/FileHandling/TextFileHandler.h"

#include <unordered_map>
#include <string>

//------------------------------------------------------------------

/*
Note: All Logging should be done through these macros

Exceptions are when rebinding colors
*/

#define LOG_TO_FILE								SS::CDebugLogger::GetInstance().SetShouldLogToFile()

#define SET_LOG_LEVEL_VERBOSE					SS::CDebugLogger::GetInstance().SetLogLevel(LogLevels::ELogLevel::Verbose)
#define SET_LOG_LEVEL_LOG						SS::CDebugLogger::GetInstance().SetLogLevel(LogLevels::ELogLevel::Log)
#define SET_LOG_LEVEL_WARNING					SS::CDebugLogger::GetInstance().SetLogLevel(LogLevels::ELogLevel::Warning)
#define SET_LOG_LEVEL_ERROR						SS::CDebugLogger::GetInstance().SetLogLevel(LogLevels::ELogLevel::Error)

#define LOG_VERBOSE(LogCat, LogMessage, ...)	SS::CDebugLogger::GetInstance().PrintLog(LogLevels::ELogLevel::Verbose, #LogCat, LogMessage, __VA_ARGS__)
#define LOG_LOG(LogCat, LogMessage, ...)		SS::CDebugLogger::GetInstance().PrintLog(LogLevels::ELogLevel::Log, #LogCat, LogMessage, __VA_ARGS__)
#define LOG_WARNING(LogCat, LogMessage, ...)	SS::CDebugLogger::GetInstance().PrintLog(LogLevels::ELogLevel::Warning, #LogCat, LogMessage, __VA_ARGS__)
#define LOG_ERROR(LogCat, LogMessage, ...)		SS::CDebugLogger::GetInstance().PrintLog(LogLevels::ELogLevel::Error, #LogCat, LogMessage, __VA_ARGS__)

//------------------------------------------------------------------

namespace SpelSylt
{
	class CTime;
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

	public:
		static CDebugLogger& GetInstance();

		void SetShouldLogToFile();

		void PrintLog(LogLevels::ELogLevel InLogLevel, const char* InLogCat, const char* InLogMessage, ...);

		void SetLogLevel(LogLevels::ELogLevel InLogLevel);
		void BindColorToLogLevel(LogLevels::ELogLevel InLogLevel, ETextColor InColor);

	private:
		using FLogColorMap = std::unordered_map<LogLevels::ELogLevel, ETextColor>;

		CDebugLogger();

		void BindDefaultColors();
		void SetTextColor(ETextColor InColor);

		bool CurrentLogLevelAllowsRequestedLogLevel(LogLevels::ELogLevel InRequestedLogLevel) const;

		void PrintToConsole(LogLevels::ELogLevel InLogLevel, const char* InLogCat, const char* InLogMessage);

		void MakeLogFileName(const CTime& InTime);

		void VerbosityLevelToString(const LogLevels::ELogLevel InLogLevel, std::string& OutString) const;

		FLogColorMap LogColorMap;
		LogLevels::ELogLevel CurrentLogLevel;

		//File Logging
		CTextFileHandler LogFileHandler;
		void PrintToFile(LogLevels::ELogLevel InLogLevel, const char* InLogCat, const char* InLogMessage);
		std::string LogFileName;
		bool ShouldLogToFile;
	};
}

namespace SS = SpelSylt;

//------------------------------------------------------------------