#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/FileHandling/Banks/ShaderBank.h"

#include <filesystem>

//------------------------------------------------------------------

SBaseAsset& SpelSylt::CShaderBank::GetAsset(const char* InAssetPath, ILoader& InLoader)
{
	if (Bank.find(InAssetPath) == Bank.end())
	{
		std::filesystem::path Path(InAssetPath);
		std::string Extension = Path.extension().string();

		/*
		ASSUMING EXTENSIONS
		.frag [5]
		.geometry [9]
		.vertex [7]
		*/
		sf::Shader::Type ShaderType;
		size_t ExtLen = Extension.size();
		bool Failed = false;
		switch (ExtLen)
		{
		case 5:
			ShaderType = sf::Shader::Type::Fragment;
			break;
		case 9:
			ShaderType = sf::Shader::Type::Geometry;
			break;
		case 7:
			ShaderType = sf::Shader::Type::Vertex;
			break;
		default:
			Failed = true;
			break;
		}
		
		Bank[InAssetPath] = SShaderAsset(ShaderType);
		if (!Failed)
		{
			InLoader.Load(InAssetPath, Bank[InAssetPath]);
		}
	}

	return Bank[InAssetPath];
}

//------------------------------------------------------------------