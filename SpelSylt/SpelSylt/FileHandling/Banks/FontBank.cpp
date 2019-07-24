#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/FileHandling/Banks/FontBank.h"

using namespace SpelSylt;

//------------------------------------------------------------------

CFontBank::CFontBank()
	: Bank()
	, Loader(nullptr)
{
}

//------------------------------------------------------------------

void CFontBank::ProvideLoader(IAsyncLoader& InLoader)
{
	Loader = &InLoader;
}

//------------------------------------------------------------------

SBaseAsset& CFontBank::GetAsset(const char* InID)
{
	if (!Bank.Contains(InID))
	{
		Bank.Add(InID);
		Loader->LoadAsync(InID, Bank.GetAsset(InID));
	}

	return Bank.GetAsset(InID);
}

//------------------------------------------------------------------
