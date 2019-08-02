#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/FileHandling/ConfigReader.h"

#include <filesystem>

//------------------------------------------------------------------

using namespace ConfigReaderInternal;
using namespace SpelSylt;

//------------------------------------------------------------------

CConfigReader::CConfigReader()
	: TextFileHandler()
{
}

//------------------------------------------------------------------

void CConfigReader::ReadConfigFile(const std::string& InPath)
{
	if (!std::filesystem::exists(InPath))
	{
		LOG_WARNING(ConfigReader, "Config file %s does not exist. Unable to open.", InPath.c_str());
		return;
	}

	TextFileHandler.OpenFile(InPath, CTextFileHandler::EFileOpenMode::Read);
	TextFileHandler.Read(CfgBuffer);
	TextFileHandler.CloseFile();
}

//------------------------------------------------------------------

bool CConfigReader::ParamExists(const std::string& InParamName) const
{
	return CfgBuffer.find(InParamName) != std::string::npos;
}

//------------------------------------------------------------------

SParamData CConfigReader::GetParamData(const std::string& InParamName) const
{
	SParamData Data;
	const size_t ParamNameStart = CfgBuffer.find(InParamName);
	
	if (ParamNameStart == std::string::npos)
	{
		Data.Valid = false;
		return Data;
	}

	const size_t ParamValueStart = CfgBuffer.find_first_of(':', ParamNameStart);
	const size_t ParamValueEnd = CfgBuffer.find_first_of(',', ParamValueStart);

	if (ParamValueStart == std::string::npos || ParamValueEnd == std::string::npos)
	{
		Data.Valid = false;
		return Data;
	}

	Data.ParamOffsetStart = ParamValueStart + 1;
	Data.ParamOffsetEnd = ParamValueEnd;

	return Data;
}

//------------------------------------------------------------------

int CConfigReader::GetAsInt(const std::string& InParamName) const
{
	std::string AsString = GetAsString(InParamName);

	return std::stoi(AsString);
}

//------------------------------------------------------------------

unsigned int CConfigReader::GetAsUint(const std::string& InParamName) const
{
	std::string AsString = GetAsString(InParamName);

	return static_cast<unsigned int>(std::stoi(AsString));
}

//------------------------------------------------------------------

float CConfigReader::GetAsFloat(const std::string& InParamName) const
{
	std::string AsString = GetAsString(InParamName);

	return std::stof(AsString);
}

//------------------------------------------------------------------

std::string CConfigReader::GetAsString(const std::string& InParamName) const
{
	SParamData Data = GetParamData(InParamName);
	
	return std::string(CfgBuffer.begin() + Data.ParamOffsetStart, CfgBuffer.begin() + Data.ParamOffsetEnd);
}

//------------------------------------------------------------------