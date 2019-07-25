#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/FileHandling/Banks/ShaderBank.h"

#include <filesystem>

#include "SpelSylt/Utility/SmallString.h"

//------------------------------------------------------------------

SBaseAsset& SpelSylt::CShaderBank::GetAsset(const char* InAssetPath, ILoader& InLoader)
{
	if (Bank.find(InAssetPath) == Bank.end())
	{
		std::filesystem::path Path(InAssetPath);

		CSmallString Extension(Path.extension().string().c_str());
		sf::Shader::Type ShaderType = TranslateToType(Extension); 
		
		Bank[InAssetPath].Type = ShaderType;
		
		if (ShaderType != sf::Shader::Type::Error)
		{
			InLoader.Load(InAssetPath, Bank[InAssetPath]);
		}
		else
		{
			Bank[InAssetPath].LoadStatus = ELoadRequestStatus::Fail;
		}
	}

	return Bank[InAssetPath];
}

//------------------------------------------------------------------

sf::Shader::Type SpelSylt::CShaderBank::TranslateToType(CSmallString& InExtension) const
{
	if (InExtension == CSmallString(".frag") || InExtension == CSmallString(".fragment"))
	{
		return sf::Shader::Type::Fragment;
	}

	if (InExtension == CSmallString(".vert") || InExtension == CSmallString(".vertex"))
	{
		return sf::Shader::Type::Vertex;
	}

	if (InExtension == CSmallString(".geom") || InExtension == CSmallString(".geometry"))
	{
		return sf::Shader::Type::Geometry;
	}

	return sf::Shader::Type::Error;
}

//------------------------------------------------------------------