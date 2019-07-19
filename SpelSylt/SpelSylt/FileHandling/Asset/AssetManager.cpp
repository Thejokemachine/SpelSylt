#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/FileHandling/Asset/AssetManager.h"

//------------------------------------------------------------------

using namespace SpelSylt;

//------------------------------------------------------------------

CAssetManager::CAssetManager()
	: TextureProvider()
{
	AddAssetProvider<STextureAsset>(TextureProvider);
}

//------------------------------------------------------------------

void SpelSylt::CAssetManager::Initialize(IAsyncLoader& InAsyncLoader)
{
	for (auto& AssetHashProviderPair : TypeToProvider)
	{
		auto& AssetProvider = AssetHashProviderPair.second;
		AssetProvider->ProvideLoader(InAsyncLoader);
	}
}

//------------------------------------------------------------------


