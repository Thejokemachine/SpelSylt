#include "SpelSylt/SpelSyltPCH.h"
#include "Texture.h"

using namespace SpelSylt;

//------------------------------------------------------------------

CTexture::CTexture()
	: Asset(nullptr)
{
}

//------------------------------------------------------------------

CTexture::CTexture(const CTexture& InOther)
	: Asset(InOther.Asset)
{
}

//------------------------------------------------------------------

CTexture::CTexture(STextureAsset& InAsset)
	: Asset(&InAsset)
{
}

//------------------------------------------------------------------

void CTexture::operator=(const CTexture& InRHS)
{
	Asset = InRHS.Asset;
}

//------------------------------------------------------------------

void CTexture::operator=(STextureAsset& InRHS)
{
	Asset = &InRHS;
}

//------------------------------------------------------------------

bool CTexture::Valid() const
{
	return Asset != nullptr;
}

//------------------------------------------------------------------

SS::STextureAsset& CTexture::Get()
{
	return *Asset;
}

//------------------------------------------------------------------