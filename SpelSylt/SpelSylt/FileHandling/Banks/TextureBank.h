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
		virtual void ProvideLoader(ILoader& InLoader) override;
		virtual SBaseAsset& GetAsset(const char* InID) override;
		//End ITextureProvider
	
	private:
	
		CAssetBank<STextureAsset> Bank;

		ILoader* AssetLoader;
	};
}

namespace SS = SpelSylt;
