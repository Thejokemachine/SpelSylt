#include "RenderQueue.h"

//------------------------------------------------------------------

namespace
{
	unsigned int LayerToInt(ERenderLayer InLayer)
	{
		return static_cast<unsigned int>(InLayer);
	}
}

//------------------------------------------------------------------

CRenderQueue::CRenderQueue()
	: Queue()
{
}

//------------------------------------------------------------------

void CRenderQueue::Enqueue(ERenderLayer InLayer, const IRenderCommand& InRenderCmd)
{
	Queue[LayerToInt(InLayer)].push_back(InRenderCmd);
}

//------------------------------------------------------------------

void CRenderQueue::ForEachCommandAtLayer(ERenderLayer InLayer, const FRenderFunction& InRenderFunction)
{
	auto& LayerCommands = Queue[LayerToInt(InLayer)];

	for (IRenderCommand& Command : LayerCommands)
	{
		InRenderFunction(Command);
	}
}

//------------------------------------------------------------------

void CRenderQueue::Clear()
{
	for(unsigned int i = 0; i < Queue.size(); ++i)
	{
		Queue[i].clear();
	}
}

//------------------------------------------------------------------