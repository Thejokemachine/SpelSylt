#pragma once

#include <string>
#include <unordered_map>
#include <type_traits>
#include <assert.h>

namespace SpelSylt
{
	template<typename TAssetType>
	class CAssetBank
	{
	public:
		CAssetBank();

		bool Contains(const char* InID) const;
		void Add(const char* InID);

		TAssetType& GetAsset(const char* InID);

	private:
		std::unordered_map<std::string, TAssetType> Vault;
	};
}

namespace SS = SpelSylt;

//------------------------------------------------------------------

template<typename TAssetType>
inline SpelSylt::CAssetBank<TAssetType>::CAssetBank()
	: Vault()
{
	static_assert(std::is_base_of<SBaseAsset, TAssetType>().value, "Asset bank must hold assets!");
}

//------------------------------------------------------------------

template<typename TAssetType>
inline bool SpelSylt::CAssetBank<TAssetType>::Contains(const char* InID) const
{
	return Vault.find(InID) != Vault.end();
}

//------------------------------------------------------------------

template<typename TAssetType>
inline void SpelSylt::CAssetBank<TAssetType>::Add(const char* InID)
{
#ifdef _DEBUG
	if (Contains(InID))
	{
		assert(false && "Always check that the asset does not already exist before calling Add!");
	}
#endif

	Vault[InID] = TAssetType();
}

//------------------------------------------------------------------

template<typename TAssetType>
inline TAssetType& SpelSylt::CAssetBank<TAssetType>::GetAsset(const char* InID)
{
#ifdef _DEBUG
	if (!Contains(InID))
	{
		assert(false && "Always check that the asset does not already exist before calling GetAsset!");
	}
#endif

	return Vault[InID];
}

//------------------------------------------------------------------