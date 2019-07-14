#pragma once

#include <functional>
#include <chrono>
#include <string>
#include <filesystem>
#include <vector>
#include <atomic>

#include "SpelSylt/Utility/Async/AsyncWorker.h"

namespace SpelSylt
{
	class CFileWatcher
		: public CAsyncWorker
	{
	public:
		using FFileChangeCallback = std::function<void()>;
		using FFileChangeTime = std::filesystem::file_time_type;
		using FWatchedFileData = std::pair<std::string, FFileChangeCallback>;

		CFileWatcher();
		~CFileWatcher();

		static bool AddFile(const char* InFileToWatch, const FFileChangeCallback& InOnChangeCallback);
		virtual void DoWork() override;
	private:
		void Check();

		static std::vector<FWatchedFileData> FilesToWatch;
		static std::vector<FFileChangeTime> FileChangeTimeLookUp;

		FFileChangeTime PreviousChangeTime;
	};
}

namespace SS = SpelSylt;