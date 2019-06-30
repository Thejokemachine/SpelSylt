#pragma once

#include "RenderCommand.h"
#include "RenderQueueInput.h"
#include "DebugDrawerInput.h"

#include <SFML/Graphics/View.hpp>

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

	sf::View Camera; //At least temporarily used as a sf::View
};
