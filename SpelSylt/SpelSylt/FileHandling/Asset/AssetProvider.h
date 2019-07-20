#pragma once

#include "SpelSylt/FileHandling/Asset/Asset.h"

//------------------------------------------------------------------

class IAsyncLoader;

//------------------------------------------------------------------

namespace SpelSylt
{
	class IAssetProvider
	{
		friend class CAssetManager;

	public:
		virtual void ProvideLoader(IAsyncLoader& InLoader) = 0;
	private:
		virtual SBaseAsset* GetAsset(const char* InAssetPath) = 0;
	};
}

namespace SS = SpelSylt;