#pragma once

#include "SpelSylt/Rendering/RenderQueueInput.h"
#include "SpelSylt/Rendering/RenderQueueOutput.h"
#include "SpelSylt/Rendering/RenderLayer.h"
#include "SpelSylt/Rendering/RenderCommand.h"
#include "SpelSylt/Memory/Containers/StaticMemoryBuffer.h"

#include <array>
#include <vector>
#include <utility>

class CRenderQueue final
	: public IRenderQueueInput
	, public IRenderQueueOutput
{
public:
	CRenderQueue();
	CRenderQueue(const CRenderQueue&) = delete;
	CRenderQueue(CRenderQueue&&) = delete;
	
	//Begin IRenderQueueInput
	virtual void Enqueue(ERenderLayer InLayer, const IRenderCommand& InRenderCmd) override;
	//End IRenderQueueInput

	//Begin IRenderQueueOutput
	virtual void ForEachCommandAtLayer(ERenderLayer InLayer, const FRenderFunction& InRenderFunc) override;
	//End IRenderQueueOutput

	void Clear();

private:
	using FRenderQueue = std::array<std::vector<IRenderCommand*>, static_cast<unsigned int>(ERenderLayer::Count)>;
	FRenderQueue Queue;

	CStaticMemoryBuffer CommandsBuffer;
};