#pragma once
#include "SpelSylt/FileHandling/Loading/AsyncLoaderInterface.h"
#include "SpelSylt/Utility/Async/AsyncWorker.h"

#include "SpelSylt/Memory/MemAllocSizes.h"

#include "SpelSylt/FileHandling/Asset/Assets.h"
#include <atomic>
#include <queue>
#include <list>
#include <string>
#include <unordered_map>

namespace SpelSylt
{
	struct SLoadHandle
	{
		SLoadHandle()
			: Path("")
			, RawAsset(nullptr)
		{}

		SLoadHandle(const char* InPath, SBaseAsset& InRawAsset)
			: Path(InPath)
			, RawAsset(&InRawAsset)
		{}

		std::string Path;
		SBaseAsset* RawAsset;
	};

	class CAsyncLoader final
		: public CAsyncWorker
		, public IAsyncLoader
	{
	public:
		CAsyncLoader();

		//Begin CAsyncWorker
		virtual void DoWork() override;
		//End CAsyncWorker

		//Begin IAsyncLoader
		virtual void LoadAsync(const char* InPath, SBaseAsset& InTo) override;
		//End IAsyncLoader
	private:
		const short MaxAssetsToLoadPerCycle = 5;

		void DoLoad(SLoadHandle& InLoadHandle);

		using FLoadQueue = std::vector<SLoadHandle>;
		FLoadQueue LoadQueue;
	};
}

namespace SS = SpelSylt;