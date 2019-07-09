#pragma once
#include "SpelSylt/Rendering/RenderLayer.h"
#include <functional>

namespace sf
{
	class RenderTarget;
}

struct IRenderCommand;

using FRenderFunction = std::function<void(const IRenderCommand&)>;


class IRenderQueueOutput
{
public:
	virtual void ForEachCommandAtLayer(ERenderLayer InLayer, const FRenderFunction& InRenderFunc) = 0;
};