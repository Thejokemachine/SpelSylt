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
		virtual SBaseAsset& GetAsset(const char* InID, ILoader& InLoader) override;
		//End ITextureProvider

	private:
		CAssetBank<SFontAsset> Bank;
	};
}

namespace SS = SpelSylt;