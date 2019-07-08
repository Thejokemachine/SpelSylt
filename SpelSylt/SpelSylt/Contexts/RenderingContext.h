#pragma once

#include "Rendering/RenderCommand.h"
#include "Rendering/RenderQueueInput.h"
#include "Debugging/Rendering/DebugDrawerInput.h"

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
