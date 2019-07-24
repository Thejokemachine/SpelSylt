#pragma once

#include "SpelSylt/Rendering/RenderLayer.h"

namespace SpelSylt
{
	struct IRenderCommand;

	class IRenderQueueInput
	{
	public:
		virtual void Enqueue(ERenderLayer InLayer, const IRenderCommand& InRenderCmd) = 0;
	};
}

namespace SS = SpelSylt;