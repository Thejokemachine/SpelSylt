#pragma once

#include "RenderCommand.h"
#include "RenderQueueInput.h"

struct SRenderingContext
{
public:
	SRenderingContext(
		IRenderQueueInput& InRenderQueueInput
	)
		: RenderQueue(InRenderQueueInput)
	{
	};

	IRenderQueueInput& RenderQueue;
};
