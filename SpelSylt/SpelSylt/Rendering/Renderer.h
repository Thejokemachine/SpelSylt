#pragma once
#include "SpelSylt/Rendering/RenderLayer.h"
#include <SFML/Graphics/Shader.hpp>

namespace sf
{
	class RenderTarget;
}
class IRenderQueueOutput;

class CRenderer
{
public:
	CRenderer();
	CRenderer(const CRenderer&) = delete;
	CRenderer(CRenderer&&) = delete;

	void RunRenderLayer(ERenderLayer InLayer, IRenderQueueOutput& InOutputRenderQueue, sf::RenderTarget& InTargetToRenderTo);
	void RunRenderAllLayers(IRenderQueueOutput& InOutputRenderQueue, sf::RenderTarget& InTargetToRenderTo);

private:
	sf::Shader NormalShader;
};