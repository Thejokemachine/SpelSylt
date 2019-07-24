#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/FileHandling/Banks/TextureBank.h"
#include "SpelSylt/FileHandling/Loading/LoaderInterface.h"

//------------------------------------------------------------------

using namespace SpelSylt;

//------------------------------------------------------------------

CTextureBank::CTextureBank()
	: Bank()
	, AssetLoader(nullptr)
{
}

//------------------------------------------------------------------

void CTextureBank::ProvideLoader(ILoader& InLoader)
{
	AssetLoader = &InLoader;
}

//------------------------------------------------------------------

SBaseAsset& CTextureBank::GetAsset(const char* InID)
{
	if (!Bank.Contains(InID))
	{
		Bank.Add(InID);
		AssetLoader->Load(InID, Bank.GetAsset(InID));
	}

	return Bank.GetAsset(InID);
}

//------------------------------------------------------------------