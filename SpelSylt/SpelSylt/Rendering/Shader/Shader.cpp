#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/Rendering/Shader/Shader.h"

#include "SpelSylt/FileHandling/Asset/AssetTypes/ShaderAsset.h"

//------------------------------------------------------------------

SpelSylt::CShader::CShader()
	: ShaderAsset(nullptr)
{
}

//------------------------------------------------------------------

void SpelSylt::CShader::operator=(const CShader& InRHS)
{
	ShaderAsset = InRHS.ShaderAsset;
}

//------------------------------------------------------------------

void SpelSylt::CShader::operator=(SShaderAsset& InRHS)
{
	ShaderAsset = &InRHS;
}

//------------------------------------------------------------------

bool SpelSylt::CShader::Valid() const
{
	return ShaderAsset != nullptr;
}

//------------------------------------------------------------------

SShaderAsset& SpelSylt::CShader::Get()
{
	return *ShaderAsset;
}

//------------------------------------------------------------------


