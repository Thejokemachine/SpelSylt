#include "SpelSyltPCH.h"

#include "TextureBank.h"
#include "AsyncLoaderInterface.h"

//------------------------------------------------------------------

CTextureBank::CTextureBank(IAsyncLoader& InAssetLoader)
	: AssetLoader(InAssetLoader)
	, Bank()
{
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
	AssetLoader.LoadAsync(InID, Bank[InID]);
}

//------------------------------------------------------------------
