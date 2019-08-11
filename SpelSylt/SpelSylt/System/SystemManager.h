#pragma once
#include "SpelSylt/Memory/Containers/StaticMemoryBuffer.h"
#include "SpelSylt/System/SystemInterface.h"
#include <vector>
#include <type_traits>

namespace SpelSylt
{
	class CRenderQueue;

	class CSystemManager
	{
	public:
		CSystemManager();
		explicit CSystemManager(B InTotalSystemsSize);
		~CSystemManager();

		void RunSystemsTick(float InDT);
		void RunSystemsRender(CRenderQueue& InRenderQueue);

		template<typename TSystem, typename ... TSystemArgs>
		void EmplaceSystem(TSystemArgs ...);
	private:
		CStaticMemoryBuffer SystemBuffer;
		std::vector<ISystem*> SystemPtrs;
	};
}

namespace SS = SpelSylt;

//------------------------------------------------------------------

template<typename TSystem, typename ...TSystemArgs>
inline void SpelSylt::CSystemManager::EmplaceSystem(TSystemArgs ... InArgs)
{
	//static_assert(is_base_of(ISystem, TSystem), "Cannot emplace a non system in the System Manager. Ensure your type derives from ISystem");
	TSystem& CreatedSystem = SystemBuffer.EmplaceToBuffer<TSystem>(InArgs...);
	SystemPtrs.push_back(&CreatedSystem);
}

//------------------------------------------------------------------

