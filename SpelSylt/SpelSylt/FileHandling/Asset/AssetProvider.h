#pragma once

#include "SpelSylt/FileHandling/Asset/Asset.h"

namespace SpelSylt
{
	class IAsyncLoader;

	class IAssetProvider
	{
		friend class CAssetManager;

	public:
		virtual void ProvideLoader(IAsyncLoader& InLoader) = 0;
		virtual SBaseAsset& GetAsset(const char* InAssetPath) = 0;
	};
}

namespace SS = SpelSylt;