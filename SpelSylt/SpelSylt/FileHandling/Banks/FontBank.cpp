#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/FileHandling/Banks/FontBank.h"

using namespace SpelSylt;

//------------------------------------------------------------------

CFontBank::CFontBank()
	: Bank()
{
}

//------------------------------------------------------------------

SBaseAsset& CFontBank::GetAsset(const char* InID, ILoader& InLoader)
{
	if (!Bank.Contains(InID))
	{
		Bank.Add(InID);
		InLoader.Load(InID, Bank.GetAsset(InID));
	}

	return Bank.GetAsset(InID);
}

//------------------------------------------------------------------
