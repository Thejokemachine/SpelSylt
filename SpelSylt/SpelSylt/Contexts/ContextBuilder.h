#pragma once
#include "SpelSylt/Contexts/GameContext.h"
#include "SpelSylt/Contexts/RenderingContext.h"

class ITimeGetter;
class IInputEventGetter;
class IAsyncLoader;
class ITextureProvider;
class CMessageQueue;
class IRenderQueueInput;
class IDebugDrawerInput;

class CContextBuilder
{
public:
	CContextBuilder();

	SGameContext* BuildGameContext(
		IInputEventGetter& InInputEventGetter,
		ITimeGetter& InTimeGetter,
		IAsyncLoader& InAsyncLoader,
		ITextureProvider& InTextureProvider,
		CMessageQueue& InMessageQueue );

	SRenderingContext* BuildRenderingContext(
		IRenderQueueInput& InRenderQueueInput,
		IDebugDrawerInput& InDebugDrawerInput );
private:
	SGameContext* BuiltGameContext;
	SRenderingContext* BuiltRenderingContext;
};