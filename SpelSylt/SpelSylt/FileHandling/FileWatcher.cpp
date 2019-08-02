#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/FileHandling/FileWatcher.h"

//------------------------------------------------------------------

using namespace SpelSylt;

std::vector<CFileWatcher::FWatchedFileData> CFileWatcher::FilesToWatch;
std::vector<CFileWatcher::FFileChangeTime> CFileWatcher::FileChangeTimeLookUp;

//------------------------------------------------------------------

namespace
{
	CFileWatcher::FFileChangeTime GetFileChangeTime(const std::string& InFilePath)
	{
		return std::filesystem::last_write_time(InFilePath);
	}

	CFileWatcher::FFileChangeTime GetFileChangeTime(const std::string& InFilePath, const CFileWatcher::FFileChangeTime& InPreviousTime)
	{
		CFileWatcher::FFileChangeTime ReturnTime;

		try 
		{ 
			ReturnTime = std::filesystem::last_write_time(InFilePath); 
		}
		catch (const std::filesystem::filesystem_error e)
		{
			ReturnTime = InPreviousTime;
		}

		return ReturnTime;
	}
}

//------------------------------------------------------------------

CFileWatcher::CFileWatcher()
{
}

//------------------------------------------------------------------

CFileWatcher::~CFileWatcher()
{
}

//------------------------------------------------------------------

bool CFileWatcher::AddFile(const char* InFileToWatch, const FFileChangeCallback& InOnChangeCallback)
{
	if (!std::filesystem::exists(InFileToWatch))
	{
		LOG_WARNING(Filewatcher, "Tried watching file '%s' that did not exist", InFileToWatch);
		return false;
	}

	FilesToWatch.push_back(FWatchedFileData(InFileToWatch, InOnChangeCallback));
	FileChangeTimeLookUp.push_back(GetFileChangeTime(FilesToWatch.back().first));

	return true;
}

//------------------------------------------------------------------

void CFileWatcher::DoWork()
{
	Check();
}

//------------------------------------------------------------------

void CFileWatcher::Check()
{
	std::vector<CFileWatcher::FWatchedFileData> FilesToWatchCache = FilesToWatch;
	std::vector<CFileWatcher::FFileChangeTime> FileChangeTimeLookUpCache = FileChangeTimeLookUp;

	const bool IsMidAdd = FilesToWatchCache.size() != FileChangeTimeLookUpCache.size();

	if (IsMidAdd)
	{
		return;
	}

	for (unsigned int i = 0; i < FilesToWatchCache.size(); ++i)
	{
		const FWatchedFileData& CurrentFileData = FilesToWatchCache[i];
		const std::string& CurrentFile = CurrentFileData.first;
		const FFileChangeCallback& CurrentFileOnChange = CurrentFileData.second;
		FFileChangeTime& CurrentFilePreviousLastChanged = FileChangeTimeLookUpCache[i];

		FFileChangeTime LastChangeTime = GetFileChangeTime(CurrentFile, LastChangeTime);

		if (LastChangeTime > CurrentFilePreviousLastChanged)
		{
			CurrentFileOnChange();
			CurrentFilePreviousLastChanged = LastChangeTime;
		}
	}
}

//------------------------------------------------------------------



