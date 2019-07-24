#pragma once
#include "SpelSylt/Contexts/GameContext.h"
#include "SpelSylt/Contexts/RenderingContext.h"

class ITimeGetter;
class IInputEventGetter;
class ILoader;
class CMessageQueue;
class IRenderQueueInput;
class IDebugDrawerInput;

namespace SpelSylt
{
	class CAssetManager;
}

class CContextBuilder
{
public:
	CContextBuilder();

	SGameContext* BuildGameContext(
		IInputEventGetter& InInputEventGetter,
		ITimeGetter& InTimeGetter,
		ILoader& InAsyncLoader,
		CMessageQueue& InMessageQueue,
		SS::CAssetManager& InAssetManager );

	SRenderingContext* BuildRenderingContext(
		IRenderQueueInput& InRenderQueueInput,
		IDebugDrawerInput& InDebugDrawerInput );
private:
	SGameContext* BuiltGameContext;
	SRenderingContext* BuiltRenderingContext;
};