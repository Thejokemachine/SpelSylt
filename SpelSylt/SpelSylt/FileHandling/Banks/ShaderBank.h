#pragma once
#include "SpelSylt/FileHandling/Asset/AssetProvider.h"

#include "SpelSylt/FileHandling/Asset/AssetTypes/ShaderAsset.h"

#include <string>
#include <unordered_map>

namespace SpelSylt
{
	class ILoader;
	class CSmallString;

	class CShaderBank
		: public IAssetProvider
	{
	public:
		CShaderBank() = default;

		//Begin IAssetProvider
		virtual SBaseAsset& GetAsset(const char* InAssetPath, ILoader& InLoader) override;
		//End IAssetProvider

	private:
		sf::Shader::Type TranslateToType(CSmallString& InExtension) const;

		std::unordered_map<std::string, SShaderAsset> Bank;
	};
}

namespace SF = SpelSylt;