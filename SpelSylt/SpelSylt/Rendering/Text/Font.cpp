#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/Rendering/Text/Font.h"
#include "SpelSylt/FileHandling/Asset/AssetTypes/FontAsset.h"

using namespace SpelSylt;

//------------------------------------------------------------------

CFont::CFont()
	: FontAsset(nullptr)
{
}

//------------------------------------------------------------------

CFont::CFont(const CFont& InOther)
{
	FontAsset = InOther.FontAsset;
}

//------------------------------------------------------------------

CFont::CFont(SFontAsset& InFontAsset)
{
	FontAsset = &InFontAsset;
}

//------------------------------------------------------------------

void CFont::operator=(const CFont& InRHS)
{
	FontAsset = InRHS.FontAsset;
}

//------------------------------------------------------------------

void CFont::operator=(SFontAsset& InRHS)
{
	FontAsset = &InRHS;
}

//------------------------------------------------------------------

bool CFont::Valid() const
{
	return FontAsset != nullptr;
}

//------------------------------------------------------------------

SFontAsset& CFont::Get()
{
	return *FontAsset;
}

//------------------------------------------------------------------

