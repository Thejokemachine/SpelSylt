#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/Rendering/Renderer.h"
#include "SpelSylt/Rendering/RenderCommand.h"
#include "SpelSylt/Rendering/RenderQueueOutput.h"

#include <SFML/Graphics/RenderTarget.hpp>

//------------------------------------------------------------------

CRenderer::CRenderer()
{
	NormalShader.loadFromFile("Shaders/SpriteNormal_FRAG.fx", sf::Shader::Type::Fragment);
}

void CRenderer::RunRenderLayer(ERenderLayer InLayer, IRenderQueueOutput& InOutputRenderQueue, sf::RenderTarget& InTargetToRenderTo)
{
	static sf::Vector3f light = {1, -0.5f, -1.0f};
	static float f = 0.f;
	f += 0.01f;
	light.x = sinf(f);

	NormalShader.setUniform("lightDir", light);

	InOutputRenderQueue.ForEachCommandAtLayer(InLayer, [this, &InTargetToRenderTo](const IRenderCommand& InCommand) {
			NormalShader.setUniform("albedo", *InCommand.GetTexture(0));
			NormalShader.setUniform("normal", *InCommand.GetTexture(1));
			InTargetToRenderTo.draw(InCommand.GetRaw(), &NormalShader);
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