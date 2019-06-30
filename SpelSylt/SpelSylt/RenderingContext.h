#pragma once

#include "RenderCommand.h"
#include "RenderQueueInput.h"
#include "DebugDrawerInput.h"

struct SRenderingContext
{
public:
	SRenderingContext() = delete;

	SRenderingContext(
		IRenderQueueInput& InRenderQueueInput,
		IDebugDrawerInput& InDebugDrawerInput 
	)
		: RenderQueue(InRenderQueueInput)
		, DebugDrawer(InDebugDrawerInput)
	{
	};

	IRenderQueueInput& RenderQueue;
	IDebugDrawerInput& DebugDrawer;
};
