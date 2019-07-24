#pragma once

#include "SpelSylt/FileHandling/Asset/Asset.h"

//------------------------------------------------------------------

class ILoader;

//------------------------------------------------------------------

namespace SpelSylt
{
	class IAssetProvider
	{
		friend class CAssetManager;

	public:
		virtual void ProvideLoader(ILoader& InLoader) = 0;
		virtual SBaseAsset& GetAsset(const char* InAssetPath) = 0;
	};
}

namespace SS = SpelSylt;