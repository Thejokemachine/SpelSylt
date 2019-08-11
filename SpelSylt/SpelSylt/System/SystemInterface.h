#pragma once

namespace SpelSylt
{
	class CRenderQueue;

	class ISystem
	{
	public:
		virtual void Tick(float InDT) {};
		virtual void Render(CRenderQueue& InRenderQueue) {};
	};
}

namespace SS = SpelSylt;