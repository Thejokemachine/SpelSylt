#pragma once

namespace SpelSylt
{
	struct SFontAsset;

	class CFont
	{
	public:
		CFont();
		CFont(const CFont& InOther);
		CFont(SFontAsset& InFontAsset);

		void operator=(const CFont& InRHS);
		void operator=(SFontAsset& InRHS);

		bool Valid() const;
		SFontAsset& Get();
	private:
		SFontAsset* FontAsset;
	};

}

namespace SS = SpelSylt;