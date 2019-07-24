#pragma once

#include "SpelSylt/FileHandling/Asset/Asset.h"

#include <SFML/Graphics/Font.hpp>

namespace SpelSylt
{
	struct SFontAsset
		: public SBaseAsset
		, sf::Font
	{
		SFontAsset()
		{
		}

	private:
		virtual void AssignData(char* InDataLocation, B InDataSize)
		{
			loadFromMemory(InDataLocation, InDataSize);
		}
	};
}

namespace SS = SpelSylt;