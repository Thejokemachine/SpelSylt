#pragma once

#include "RenderQueueInput.h"
#include "RenderQueueOutput.h"
#include "RenderLayer.h"
#include "RenderCommand.h"

#include <array>
#include <vector>

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

private:
	using FRenderQueue = std::array<std::vector<IRenderCommand>, static_cast<unsigned int>(ERenderLayer::Count)>;

	FRenderQueue Queue;
};