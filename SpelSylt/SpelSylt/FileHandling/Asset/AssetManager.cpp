#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/FileHandling/Asset/AssetManager.h"

//------------------------------------------------------------------

using namespace SpelSylt;

//------------------------------------------------------------------

CAssetManager::CAssetManager()
	: AsyncLoader(nullptr)
	, SynchronousLoader(nullptr)
	, TextureProvider()
	, FontProvider()
{
	AddAssetProvider<STextureAsset>(TextureProvider);
	AddAssetProvider<SFontAsset>(FontProvider);
}

//------------------------------------------------------------------

void CAssetManager::ProvideLoaders(CAsyncLoader& InAsyncLoader, CSynchronousLoader& InSynchronousLoader)
{
	AsyncLoader = &InAsyncLoader;
	SynchronousLoader = &InSynchronousLoader;
}

//------------------------------------------------------------------


