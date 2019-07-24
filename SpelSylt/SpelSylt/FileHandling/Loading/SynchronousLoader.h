#pragma once

#include "SpelSylt/FileHandling/Loading/LoaderInterface.h"

namespace SpelSylt
{
	class CSynchronousLoader final
		: public ILoader
	{
	public:
		CSynchronousLoader();

		//Begin ILoader
		virtual void Load(const char* InPath, SBaseAsset& InTo) override;
		//End ILoader
	};
}

namespace SS = SpelSylt;