#include "SpelSyltPCH.h"

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
	, CommandsBuffer(1048 * 2 * 2 * 2 * 2 * 2)
{
}

//------------------------------------------------------------------

void CRenderQueue::Enqueue(ERenderLayer InLayer, const IRenderCommand& InRenderCmd)
{
	unsigned short SizeOfCommandType = 0;

	switch (InRenderCmd.GetCommandType())
	{
	case ECommandType::Sprite:
		SizeOfCommandType = sizeof(SSpriteRenderCommand);
		break;
	default:
		break;
	}

	IRenderCommand* Command = reinterpret_cast<IRenderCommand*>(CommandsBuffer.AddCustomData(&InRenderCmd, SizeOfCommandType));
	Queue[LayerToInt(InLayer)].push_back(Command);
}

//------------------------------------------------------------------

void CRenderQueue::ForEachCommandAtLayer(ERenderLayer InLayer, const FRenderFunction& InRenderFunction)
{
	auto& LayerCommands = Queue[LayerToInt(InLayer)];

	for (IRenderCommand* Command : LayerCommands)
	{
		InRenderFunction(*Command);
	}
}

//------------------------------------------------------------------

void CRenderQueue::Clear()
{
	for(unsigned int i = 0; i < Queue.size(); ++i)
	{
		Queue[i].clear();
	}

	CommandsBuffer.Flush();
}

//------------------------------------------------------------------