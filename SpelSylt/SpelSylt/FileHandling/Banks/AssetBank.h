#pragma once

#include "SpelSylt/FileHandling/Asset/AssetProvider.h"

#include <string>
#include <unordered_map>
#include <type_traits>
#include <assert.h>

namespace SpelSylt
{
	template<typename TAssetType>
	class CAssetBank final
		: public IAssetProvider
	{
	public:
		CAssetBank();

		//Begin IAssetProvider
		virtual TAssetType& GetAsset(const char* InAssetPath, ILoader& InLoader) override;
		//End IAssetProvider

	private:
		bool ContainsAsset(const char* InAssetPath) const;
		void AddAsset(const char* InAssetPath, ILoader& InLoader);

		using TVault = std::unordered_map<std::string, TAssetType>;
		TVault Vault;
	};
}

namespace SS = SpelSylt;

//------------------------------------------------------------------

template<typename TAssetType>
inline SpelSylt::CAssetBank<TAssetType>::CAssetBank()
	: Vault()
{
}

//------------------------------------------------------------------

template<typename TAssetType>
inline TAssetType& SpelSylt::CAssetBank<TAssetType>::GetAsset(const char* InAssetPath, ILoader& InLoader)
{
	if (!ContainsAsset(InAssetPath))
	{
		AddAsset(InAssetPath, InLoader);
	}

	return Vault[InAssetPath];
}

//------------------------------------------------------------------

template<typename TAssetType>
inline bool SpelSylt::CAssetBank<TAssetType>::ContainsAsset(const char* InAssetPath) const
{
	return Vault.find(InAssetPath) != Vault.end();
}

//------------------------------------------------------------------

template<typename TAssetType>
inline void SpelSylt::CAssetBank<TAssetType>::AddAsset(const char* InAssetPath, ILoader& InLoader)
{
	Vault[InAssetPath] = TAssetType();
	InLoader.Load(InAssetPath, Vault[InAssetPath]);
}

//------------------------------------------------------------------