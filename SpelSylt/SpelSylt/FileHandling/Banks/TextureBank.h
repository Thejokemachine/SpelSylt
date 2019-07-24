#pragma once

#include "SpelSylt/FileHandling/Asset/AssetProvider.h"

#include "SpelSylt/FileHandling/Asset/Assets.h"

#include "SpelSylt/FileHandling/Banks/AssetBank.h"

#include <string>


namespace SpelSylt
{
	class ILoader;

	class CTextureBank final
		: public IAssetProvider
	{
	public:
		CTextureBank();
	
		//Begin ITextureProvider
		virtual SBaseAsset& GetAsset(const char* InID, ILoader& InLoader) override;
		//End ITextureProvider
	
	private:
		CAssetBank<STextureAsset> Bank;
	};
}

namespace SS = SpelSylt;
