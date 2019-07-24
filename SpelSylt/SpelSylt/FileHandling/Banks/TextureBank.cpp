#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/FileHandling/Banks/TextureBank.h"
#include "SpelSylt/FileHandling/Loading/LoaderInterface.h"

//------------------------------------------------------------------

using namespace SpelSylt;

//------------------------------------------------------------------

CTextureBank::CTextureBank()
	: Bank()
{
}

//------------------------------------------------------------------

SBaseAsset& CTextureBank::GetAsset(const char* InID, ILoader& InLoader)
{
	if (!Bank.Contains(InID))
	{
		Bank.Add(InID);
		InLoader.Load(InID, Bank.GetAsset(InID));
	}

	return Bank.GetAsset(InID);
}

//------------------------------------------------------------------