#pragma once

#include "SpelSylt/FileHandling/Asset/Asset.h"

#include <SFML/Graphics/Shader.hpp>
#include <string>

namespace SpelSylt
{
	struct SShaderAsset
		: public SBaseAsset
		, sf::Shader
	{
		friend class CShaderBank;
		
		SShaderAsset()
			: Type(sf::Shader::Type::Error)
		{
		}

		SShaderAsset(const SShaderAsset& InOther)
			: Type(InOther.Type)
		{
		}

		void operator=(const SShaderAsset& InRHS)
		{
			Type = InRHS.Type;
		}

	private:
		virtual void AssignData(char* InDataLocation, B InDataSize)
		{
			std::string ShaderData(InDataLocation, InDataSize);
			loadFromMemory(ShaderData, Type);
		}

		sf::Shader::Type Type;
	};

}

namespace SS = SpelSylt;