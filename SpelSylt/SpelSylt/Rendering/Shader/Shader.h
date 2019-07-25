#pragma once

namespace SpelSylt
{
	struct SShaderAsset;

	class CShader
	{
	public:
		CShader();

		void operator=(const CShader& InRHS);
		void operator=(SShaderAsset& InRHS);

		bool Valid() const;
		SShaderAsset& Get();
	private:
		SShaderAsset* ShaderAsset;
	};
}

namespace SS = SpelSylt;