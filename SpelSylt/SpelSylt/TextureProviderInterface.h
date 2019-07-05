#pragma once

struct STextureAsset;

class ITextureProvider
{
public:
	virtual const STextureAsset& GetTexture(const char* InID) const = 0;

};