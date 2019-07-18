#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/Rendering/Renderer.h"
#include "SpelSylt/Rendering/RenderCommand.h"
#include "SpelSylt/Rendering/RenderQueueOutput.h"

#include <SFML/Graphics/RenderTarget.hpp>

//------------------------------------------------------------------

void CRenderer::RunRenderLayer(ERenderLayer InLayer, IRenderQueueOutput& InOutputRenderQueue, sf::RenderTarget& InTargetToRenderTo)
{
	InOutputRenderQueue.ForEachCommandAtLayer(InLayer, [&InTargetToRenderTo](const IRenderCommand& InCommand) {
			InTargetToRenderTo.draw(InCommand.GetRaw());
		}
	);
}

//------------------------------------------------------------------

void CRenderer::RunRenderAllLayers(IRenderQueueOutput& InOutputRenderQueue, sf::RenderTarget& InTargetToRenderTo)
{
	const unsigned int MaxLayersAsInt = static_cast<unsigned int>(ERenderLayer::Count);

	for (unsigned int i = 0; i < MaxLayersAsInt; ++i)
	{
		RunRenderLayer(static_cast<ERenderLayer>(i), InOutputRenderQueue, InTargetToRenderTo);
	}
}

//------------------------------------------------------------------