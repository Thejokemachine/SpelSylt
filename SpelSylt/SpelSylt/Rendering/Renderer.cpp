#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/Rendering/Renderer.h"
#include "SpelSylt/Rendering/RenderCommand.h"
#include "SpelSylt/Rendering/RenderQueueOutput.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "FullScreenPass.h"
#include "BlackAndWhitePass.h"

//------------------------------------------------------------------

using namespace SpelSylt;

CRenderer::CRenderer(CAssetManager& aAssetManager) :
	AssetManager(aAssetManager)
{

}

void CRenderer::RunRenderLayer(ERenderLayer InLayer, IRenderQueueOutput& InOutputRenderQueue, sf::RenderTarget& InTargetToRenderTo)
{
	InOutputRenderQueue.ForEachCommandAtLayer(InLayer, [&InTargetToRenderTo](const IRenderCommand& InCommand) {
		InTargetToRenderTo.draw(InCommand.GetRaw(), InCommand.RenderState.Shader);
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

	// Fullscreen pass example:
	/*
	if (FullScreenTexture.getSize().x <= 0) {
		FullScreenTexture.create(InTargetToRenderTo.getSize().x, InTargetToRenderTo.getSize().y);
	}

	FullScreenTexture.clear();
	FullScreenTexture.setActive();
	FullScreenTexture.setView(InTargetToRenderTo.getView());

	for (unsigned int i = 0; i < MaxLayersAsInt; ++i)
	{
		RunRenderLayer(static_cast<ERenderLayer>(i), InOutputRenderQueue, FullScreenTexture);
	}

	BlackAndWhitePass pass(AssetManager);
	pass.RunPass(InTargetToRenderTo, { &FullScreenTexture.getTexture() });
	*/
}

//------------------------------------------------------------------