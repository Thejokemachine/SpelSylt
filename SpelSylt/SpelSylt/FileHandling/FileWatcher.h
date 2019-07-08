#pragma once

#include <functional>
#include <chrono>

#include <thread>
#include <atomic>
#include <string>
#include <filesystem>
#include <vector>

class CFileWatcher
{
public:
	using FFileChangeCallback = std::function<void()>;
	using FFileChangeTime = std::filesystem::file_time_type;

	CFileWatcher();
	~CFileWatcher();

	bool AddFile(const char* InFileToWatch, const FFileChangeCallback& InOnChangeCallback);
	void RequestStop();
	bool IsStopped() const;
private:
	void StartWatch();
	void Check();
	FFileChangeTime GetFileChangeTime(const std::string& InFilePath);

	FFileChangeCallback OnChange;

	std::atomic_bool ShouldStop;
	std::atomic_bool HaveStopped;
	
	using FWatchedFileData = std::pair<std::string, FFileChangeCallback>;
	std::vector<FWatchedFileData> FilesToWatch;
	std::vector<FFileChangeTime> FileChangeTimeLookUp;

	std::thread WatchThread;

	FFileChangeTime PreviousChangeTime;
};