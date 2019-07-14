#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/FileHandling/Banks/TextureBank.h"
#include "SpelSylt/FileHandling/Loading/AsyncLoaderInterface.h"

//------------------------------------------------------------------

CTextureBank::CTextureBank()
	: Bank()
	, AssetLoader(nullptr)
{
}

//------------------------------------------------------------------

void CTextureBank::ProvideLoader(IAsyncLoader& InLoader)
{
	AssetLoader = &InLoader;
}

//------------------------------------------------------------------

const STextureAsset& CTextureBank::GetTexture(const char* InID) const
{
	if (!AssetLoaded(InID))
	{
		AddAsset(InID);
	}

	return Bank[InID];
}

//------------------------------------------------------------------

bool CTextureBank::AssetLoaded(const char* InID) const
{
	return (Bank.find(InID) != Bank.end());
}

//------------------------------------------------------------------

void CTextureBank::AddAsset(const char* InID) const 
{
	Bank[InID] = STextureAsset();
	AssetLoader->LoadAsync(InID, Bank[InID]);
}

//------------------------------------------------------------------
