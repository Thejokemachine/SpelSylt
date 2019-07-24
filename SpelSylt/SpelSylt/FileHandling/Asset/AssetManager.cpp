#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/FileHandling/Asset/AssetManager.h"

//------------------------------------------------------------------

using namespace SpelSylt;

//------------------------------------------------------------------

CAssetManager::CAssetManager()
	: TextureProvider()
	, FontProvider()
{
	AddAssetProvider<STextureAsset>(TextureProvider);
	AddAssetProvider<SFontAsset>(FontProvider);
}

//------------------------------------------------------------------

void CAssetManager::Initialize(ILoader& InAsyncLoader)
{
	for (auto& AssetHashProviderPair : TypeToProvider)
	{
		auto& AssetProvider = AssetHashProviderPair.second;
		AssetProvider->ProvideLoader(InAsyncLoader);
	}
}

//------------------------------------------------------------------


