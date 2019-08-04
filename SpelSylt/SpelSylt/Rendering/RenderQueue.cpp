#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/Rendering/RenderQueue.h"

using namespace SpelSylt;

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
	, CommandsBuffer(512_mb)
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
	case ECommandType::Animation:
		SizeOfCommandType = sizeof(SSpriteAnimationRenderCommand);
		break;
	case ECommandType::Text:
		SizeOfCommandType = sizeof(STextRenderCommand);
		break;
	case ECommandType::SFTexture:
		SizeOfCommandType = sizeof(SSFSpriteRenderCommand);
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