#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/FileHandling/FileWatcher.h"

//------------------------------------------------------------------

CFileWatcher::CFileWatcher()
	: FilesToWatch()
	, FileChangeTimeLookUp()
	, ShouldStop(false)
	, HaveStopped(false)
{
}

//------------------------------------------------------------------

CFileWatcher::~CFileWatcher()
{
	RequestStop();
	while (!IsStopped());
	WatchThread.join();
}

//------------------------------------------------------------------

bool CFileWatcher::AddFile(const char* InFileToWatch, const FFileChangeCallback& InOnChangeCallback)
{
	const bool ShouldStart = (FilesToWatch.size() == 0);

	if (!std::filesystem::exists(InFileToWatch))
	{
		LOG_WARNING(Filewatcher, "Tried watching file '%s' that did not exist", InFileToWatch);
		return false;
	}

	FilesToWatch.push_back(FWatchedFileData(InFileToWatch, InOnChangeCallback));
	FileChangeTimeLookUp.push_back(GetFileChangeTime(FilesToWatch.back().first));

	if (ShouldStart)
	{
		WatchThread = std::thread([&]() { StartWatch(); });
	}
	return true;
}

//------------------------------------------------------------------

void CFileWatcher::RequestStop()
{
	ShouldStop = true;
}

//------------------------------------------------------------------

bool CFileWatcher::IsStopped() const
{
	return HaveStopped;
}

//------------------------------------------------------------------

void CFileWatcher::StartWatch()
{
	while (!ShouldStop)
	{
		Check();
		std::this_thread::yield();
	}
}

//------------------------------------------------------------------

void CFileWatcher::Check()
{
	const unsigned int FilesCount = static_cast<unsigned int>(FilesToWatch.size());

	for (unsigned int i = 0; i < FilesCount; ++i)
	{
		const FWatchedFileData& CurrentFileData = FilesToWatch[i];
		const std::string& CurrentFile = CurrentFileData.first;
		const FFileChangeCallback& CurrentFileOnChange = CurrentFileData.second;
		FFileChangeTime& CurrentFilePreviousLastChanged = FileChangeTimeLookUp[i];

		FFileChangeTime LastChangeTime = GetFileChangeTime(CurrentFile);

		if (LastChangeTime > CurrentFilePreviousLastChanged)
		{
			CurrentFileOnChange();
			CurrentFilePreviousLastChanged = LastChangeTime;
		}
	}
}
//------------------------------------------------------------------

CFileWatcher::FFileChangeTime CFileWatcher::GetFileChangeTime(const std::string& InFilePath)
{
	return std::filesystem::last_write_time(InFilePath);
}

//------------------------------------------------------------------