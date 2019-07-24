#pragma once
#include "SpelSylt/Rendering/RenderLayer.h"

namespace sf
{
	class RenderTarget;
}

namespace SpelSylt
{
	class IRenderQueueOutput;

	class CRenderer
	{
	public:
		CRenderer() = default;
		CRenderer(const CRenderer&) = delete;
		CRenderer(CRenderer&&) = delete;

		void RunRenderLayer(ERenderLayer InLayer, IRenderQueueOutput& InOutputRenderQueue, sf::RenderTarget& InTargetToRenderTo);
		void RunRenderAllLayers(IRenderQueueOutput& InOutputRenderQueue, sf::RenderTarget& InTargetToRenderTo);
	};
}

namespace SS = SpelSylt;