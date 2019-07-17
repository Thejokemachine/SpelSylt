#pragma once

#include <string>

namespace FileMutator
{
	static std::string GetFileNameWithoutSuffix(const std::string& InFileName)
	{
		std::string::const_iterator FileNameBegin(InFileName.begin());
		std::string::const_iterator FileNameSuffixBegin(InFileName.begin() + InFileName.find_last_of('_'));

		std::string FileNameNoSuffix(FileNameBegin, FileNameSuffixBegin);
		return FileNameNoSuffix;
	}
	
	static std::string GetFileSuffix(const std::string& InFileName)
	{
		std::string::const_iterator SuffixStart(InFileName.begin() + (InFileName.find_last_of('_')));
		std::string::const_iterator SuffixEnd(SuffixStart + 3);
		std::string Suffix(SuffixStart, SuffixEnd);
		return Suffix;
	}

}