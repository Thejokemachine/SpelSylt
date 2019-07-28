#pragma once
#include "SpelSylt/Rendering/RenderLayer.h"

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Shader.hpp>

namespace sf
{
	class RenderTarget;
}

namespace SpelSylt
{
	class IRenderQueueOutput;
	class CAssetManager;

	class CRenderer
	{
	public:
		CRenderer(CAssetManager& aAssetManager);
		CRenderer(const CRenderer&) = delete;
		CRenderer(CRenderer&&) = delete;

		void RunRenderLayer(ERenderLayer InLayer, IRenderQueueOutput& InOutputRenderQueue, sf::RenderTarget& InTargetToRenderTo);
		void RunRenderAllLayers(IRenderQueueOutput& InOutputRenderQueue, sf::RenderTarget& InTargetToRenderTo);

	private:

		sf::Vertex FullScreenVertices[3];
		sf::RenderTexture FullScreenTexture;
		sf::Shader FullScreenShader;

		CAssetManager& AssetManager;
	};
}

namespace SS = SpelSylt;