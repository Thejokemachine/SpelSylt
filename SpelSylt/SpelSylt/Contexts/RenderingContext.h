#pragma once

#include "SpelSylt/Rendering/RenderCommand.h"
#include "SpelSylt/Rendering/RenderQueueInput.h"
#include "SpelSylt/Debugging/Rendering/DebugDrawerInput.h"

#include <SFML/Graphics/View.hpp>

namespace SpelSylt
{
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
}

namespace SS = SpelSylt;