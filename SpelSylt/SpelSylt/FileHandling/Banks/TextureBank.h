#pragma once

#include "SpelSylt/FileHandling/Banks/TextureProviderInterface.h"

#include "SpelSylt/FileHandling/Asset/Assets.h"

#include <string>
#include <unordered_map>

class IAsyncLoader;

class CTextureBank final
	: public ITextureProvider
{
public:
	CTextureBank();

	void ProvideLoader(IAsyncLoader& InLoader);

	//Begin ITextureProvider
	virtual const STextureAsset& GetTexture(const char* InID) const;
	//End ITextureProvider

private:
	bool AssetLoaded(const char* InID) const;
	void AddAsset(const char* InID) const;

	using FBank = std::unordered_map<std::string, STextureAsset>;
	mutable FBank Bank;

	IAsyncLoader* AssetLoader;
};
