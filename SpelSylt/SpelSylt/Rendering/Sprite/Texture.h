#pragma once

namespace SpelSylt
{
	struct STextureAsset;

	class CTexture
	{
	public:
		CTexture();
		explicit CTexture(const CTexture& InOther);
		explicit CTexture(STextureAsset& InAsset);

		void operator=(const CTexture& InRHS);
		void operator=(STextureAsset& InRHS);

		bool Valid() const;
		STextureAsset& Get();
	private:
		STextureAsset* Asset;
	};
}

namespace SS = SpelSylt;