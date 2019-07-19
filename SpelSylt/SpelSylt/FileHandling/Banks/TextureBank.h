#pragma once

#include "SpelSylt/FileHandling/Asset/AssetProvider.h"

#include "SpelSylt/FileHandling/Asset/Assets.h"

#include <string>
#include <unordered_map>

class IAsyncLoader;

namespace SpelSylt
{
	class CTextureBank final
		: public IAssetProvider
	{
	public:
		CTextureBank();
	
		void ProvideLoader(IAsyncLoader& InLoader);
	
		//Begin ITextureProvider
		virtual SBaseAsset* GetAsset(const char* InID) override;
		//End ITextureProvider
	
	private:
		bool AssetLoaded(const char* InID) const;
		void AddAsset(const char* InID);
	
		using FBank = std::unordered_map<std::string, STextureAsset>;
		FBank Bank;
	
		IAsyncLoader* AssetLoader;
	};
}

namespace SS = SpelSylt;
