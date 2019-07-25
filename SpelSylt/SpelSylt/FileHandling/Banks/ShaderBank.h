#pragma once
#include "SpelSylt/FileHandling/Asset/AssetProvider.h"

#include "SpelSylt/FileHandling/Asset/AssetTypes/ShaderAsset.h"

#include <string>
#include <unordered_map>

namespace SpelSylt
{
	class ILoader;

	class CShaderBank
		: public IAssetProvider
	{
	public:
		CShaderBank() = default;

		//Begin IAssetProvider
		virtual SBaseAsset& GetAsset(const char* InAssetPath, ILoader& InLoader) override;
		//End IAssetProvider

	private:
		std::unordered_map<std::string, SShaderAsset> Bank;
	};
}

namespace SF = SpelSylt;