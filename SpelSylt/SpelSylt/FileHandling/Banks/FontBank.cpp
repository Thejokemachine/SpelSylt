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

void CFontBank::ProvideLoader(ILoader& InLoader)
{
	Loader = &InLoader;
}

//------------------------------------------------------------------

SBaseAsset& CFontBank::GetAsset(const char* InID)
{
	if (!Bank.Contains(InID))
	{
		Bank.Add(InID);
		Loader->Load(InID, Bank.GetAsset(InID));
	}

	return Bank.GetAsset(InID);
}

//------------------------------------------------------------------
