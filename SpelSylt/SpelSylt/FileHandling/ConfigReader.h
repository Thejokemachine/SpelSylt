#pragma once
#include "SpelSylt/FileHandling/TextFileHandler.h"

#include <string>

namespace ConfigReaderInternal
{
	struct SParamData
	{
		SParamData()
			: Valid(true)
			, ParamOffsetStart(0)
			, ParamOffsetEnd(0)
		{
		}

		bool Valid;
		size_t ParamOffsetStart;
		size_t ParamOffsetEnd;
	};
}

class CConfigReader
{
public:
	CConfigReader();

	void ReadConfigFile(const std::string& InPath);

	bool ParamExists(const std::string& InParamName) const;

	int GetAsInt(const std::string& InParamName) const;
	unsigned int GetAsUint(const std::string& InParamName) const;
	float GetAsFloat(const std::string& InParamName) const;
	std::string GetAsString(const std::string& InParamName) const;
private:
	ConfigReaderInternal::SParamData GetParamData(const std::string& InParamName) const;

	CTextFileHandler TextFileHandler;
	std::string CfgBuffer;
};