#pragma once

namespace SpelSylt
{
	struct SBaseAsset;
	struct SLoadRequestTicket;

	class ILoader
	{
	public:
		virtual void Load(const char* Path, SBaseAsset& InTo) = 0;
	};
}

namespace SS = SpelSylt;