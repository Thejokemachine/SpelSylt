#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/FileHandling/Banks/TextureBank.h"
#include "SpelSylt/FileHandling/Loading/AsyncLoaderInterface.h"

//------------------------------------------------------------------

using namespace SpelSylt;

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

SBaseAsset* CTextureBank::GetAsset(const char* InID)
{
	if (!AssetLoaded(InID))
	{
		AddAsset(InID);
	}

	return &Bank[InID];
}

//------------------------------------------------------------------

bool CTextureBank::AssetLoaded(const char* InID) const
{
	return (Bank.find(InID) != Bank.end());
}

//------------------------------------------------------------------

void CTextureBank::AddAsset(const char* InID)
{
	Bank[InID] = STextureAsset();
	AssetLoader->LoadAsync(InID, Bank[InID]);
}

//------------------------------------------------------------------
