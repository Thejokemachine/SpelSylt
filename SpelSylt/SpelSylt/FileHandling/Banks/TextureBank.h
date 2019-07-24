#pragma once

#include "SpelSylt/FileHandling/Asset/AssetProvider.h"

#include "SpelSylt/FileHandling/Asset/Assets.h"

#include "SpelSylt/FileHandling/Banks/AssetBank.h"

#include <string>

class IAsyncLoader;

namespace SpelSylt
{
	class CTextureBank final
		: public IAssetProvider
	{
	public:
		CTextureBank();
	
		//Begin ITextureProvider
		virtual void ProvideLoader(IAsyncLoader& InLoader) override;
		virtual SBaseAsset& GetAsset(const char* InID) override;
		//End ITextureProvider
	
	private:
	
		CAssetBank<STextureAsset> Bank;

		IAsyncLoader* AssetLoader;
	};
}

namespace SS = SpelSylt;
