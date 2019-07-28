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
			Data = new char[InDataSize];
			DataSize = InDataSize;

			memcpy_s(Data, DataSize, InDataLocation, InDataSize);

			loadFromMemory(Data, DataSize);
		}
	
		char* Data;
		B DataSize;
	};
}

namespace SS = SpelSylt;