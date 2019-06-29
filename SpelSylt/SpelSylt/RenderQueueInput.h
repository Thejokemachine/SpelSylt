#pragma once

#include "RenderLayer.h"

struct IRenderCommand;

class IRenderQueueInput
{
public:
	virtual void Enqueue(ERenderLayer InLayer, const IRenderCommand& InRenderCmd) = 0;
};