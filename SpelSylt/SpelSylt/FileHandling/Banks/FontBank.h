#pragma once
#include "SpelSylt/FileHandling/Asset/AssetProvider.h"
#include "SpelSylt/FileHandling/Asset/Assets.h"

#include "SpelSylt/FileHandling/Banks/AssetBank.h"

namespace SpelSylt
{
	class CFontBank
		: public IAssetProvider
	{
	public:
		CFontBank();

		//Begin ITextureProvider
		virtual void ProvideLoader(IAsyncLoader& InLoader) override;
		virtual SBaseAsset& GetAsset(const char* InID) override;
		//End ITextureProvider

	private:
		CAssetBank<SFontAsset> Bank;

		IAsyncLoader* Loader;
	};
}

namespace SS = SpelSylt;