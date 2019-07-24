#pragma once
#include "SpelSylt/FileHandling/Asset/AssetProvider.h"

#include "SpelSylt/Debugging/Logging/DebugLogger.h"
#include <unordered_map>
#include <type_traits>

//Providers
#include "SpelSylt/FileHandling/Banks/TextureBank.h"
#include "SpelSylt/FileHandling/Banks/FontBank.h"

class ILoader;

namespace SpelSylt
{
	class CAssetManager
	{
	public:
		CAssetManager();

		void Initialize(ILoader& InAsyncLoader);

		template<typename TAssetType>
		TAssetType& GetAsset(const char* InAssetPath);

		template<typename TAssetType>
		void AddAssetProvider(IAssetProvider& InProvider);

	private:
		using FAssetTypeHash = size_t;
		using FTypeHashToProviderLookupTable = std::unordered_map<size_t, IAssetProvider*>;
		
		template<typename TAssetType>
		FAssetTypeHash GetAssetType() const;

		FTypeHashToProviderLookupTable TypeToProvider;

		//Todo: Add all asset providers here. Ensure they are also added in construction
		CTextureBank TextureProvider;
		CFontBank FontProvider;

	};
}

namespace SS = SpelSylt;

//------------------------------------------------------------------

template<typename TAssetType>
inline TAssetType& SpelSylt::CAssetManager::GetAsset(const char* InAssetPath)
{
	static_assert(std::is_base_of<SBaseAsset, TAssetType>::value, "Can only get asset types derrived from the Base Asset");

	FAssetTypeHash AssetTypeHash = GetAssetType<TAssetType>();
	IAssetProvider* AssetProvider = TypeToProvider[AssetTypeHash];

	if (!AssetProvider)
	{
		LOG_ERROR(LogAssetManager, "Tried getting asset provider for type that did not exist?");
	}

	SBaseAsset* RawAsset = &AssetProvider->GetAsset(InAssetPath);
	TAssetType* Asset = reinterpret_cast<TAssetType*>(RawAsset);
	return *Asset;
}

//------------------------------------------------------------------

template<typename TAssetType>
inline void SpelSylt::CAssetManager::AddAssetProvider(IAssetProvider& InProvider)
{
	FAssetTypeHash TypeHash = GetAssetType<TAssetType>();

	if (TypeToProvider.find(TypeHash) != TypeToProvider.end())
	{
		LOG_WARNING(LogAssetManager, "Tried adding asset provider that already existed within the AssetManager?");
		return;
	}

	TypeToProvider[TypeHash] = &InProvider;
}

//------------------------------------------------------------------

template<typename TAssetType>
inline SpelSylt::CAssetManager::FAssetTypeHash SpelSylt::CAssetManager::GetAssetType() const
{
	return typeid(TAssetType).hash_code();
}

//------------------------------------------------------------------

//------------------------------------------------------------------