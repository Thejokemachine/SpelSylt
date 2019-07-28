#pragma once
#include "SpelSylt/FileHandling/Asset/AssetProvider.h"

#include "SpelSylt/Debugging/Logging/DebugLogger.h"
#include <unordered_map>
#include <type_traits>

#include "SpelSylt/FileHandling/Loading/AsyncLoader.h"
#include "SpelSylt/FileHandling/Loading/SynchronousLoader.h"

#include "SpelSylt/FileHandling/Banks/AssetBank.h"
#include "SpelSylt/FileHandling/Banks/ShaderBank.h"
#include "SpelSylt/FileHandling/Asset/Assets.h"

namespace SpelSylt
{
	enum ELoadSettings : bool
	{
		Async = true,
		Synchronous = false
	};

	class CAssetManager
	{
	public:
		CAssetManager();

		void ProvideLoaders(CAsyncLoader& InAsyncLoader, CSynchronousLoader& InSynchronousLoader);

		template<typename TAssetType>
		TAssetType& GetAsset(const char* InAssetPath, ELoadSettings InSetting = ELoadSettings::Async);

		template<typename TAssetType>
		void AddAssetProvider(IAssetProvider& InProvider);

	private:
		using FAssetTypeHash = size_t;
		using FTypeHashToProviderLookupTable = std::unordered_map<size_t, IAssetProvider*>;
		
		template<typename TAssetType>
		FAssetTypeHash GetAssetType() const;

		FTypeHashToProviderLookupTable TypeToProvider;

		CAsyncLoader* AsyncLoader;
		CSynchronousLoader* SynchronousLoader;

		//Todo: Add all asset providers here. Ensure they are also added in construction
		CAssetBank<STextureAsset> TextureProvider;
		CAssetBank<SFontAsset> FontProvider;
		CAssetBank<SAnimationAsset> AnimationProvider;
		CShaderBank ShaderProvider;
	};
}

namespace SS = SpelSylt;

//------------------------------------------------------------------

template<typename TAssetType>
inline TAssetType& SpelSylt::CAssetManager::GetAsset(const char* InAssetPath, ELoadSettings InSetting)
{
	static_assert(std::is_base_of<SBaseAsset, TAssetType>::value, "Can only get asset types derrived from the Base Asset");

	FAssetTypeHash AssetTypeHash = GetAssetType<TAssetType>();
	IAssetProvider* AssetProvider = TypeToProvider[AssetTypeHash];

	if (!AssetProvider)
	{
		LOG_ERROR(LogAssetManager, "Tried getting asset provider for type that did not exist?");
	}

	ILoader* UseLoader = nullptr;
	if (InSetting == ELoadSettings::Async)
	{
		UseLoader = AsyncLoader;
	}
	else
	{
		UseLoader = SynchronousLoader;
	}

	SBaseAsset* RawAsset = &AssetProvider->GetAsset(InAssetPath, *UseLoader);
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
