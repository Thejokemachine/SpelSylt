#pragma once

#include "SpelSylt/FileHandling/Asset/Asset.h"

namespace SpelSylt
{
	class ILoader;

	class IAssetProvider
	{
		friend class CAssetManager;

	public:
		virtual SBaseAsset& GetAsset(const char* InAssetPath, ILoader& InLoader) = 0;
	};
}

namespace SS = SpelSylt;