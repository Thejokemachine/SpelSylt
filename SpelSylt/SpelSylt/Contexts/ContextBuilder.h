#pragma once
#include "SpelSylt/Contexts/GameContext.h"
#include "SpelSylt/Contexts/RenderingContext.h"

namespace SpelSylt
{
	class ITimeGetter;
	class IInputEventGetter;
	class IAsyncLoader;
	class CMessageQueue;
	class IRenderQueueInput;
	class IDebugDrawerInput;
	class CAssetManager;

	class CContextBuilder
	{
	public:
		CContextBuilder();

		SGameContext* BuildGameContext(
			IInputEventGetter& InInputEventGetter,
			ITimeGetter& InTimeGetter,
			IAsyncLoader& InAsyncLoader,
			CMessageQueue& InMessageQueue,
			SS::CAssetManager& InAssetManager);

		SRenderingContext* BuildRenderingContext(
			IRenderQueueInput& InRenderQueueInput,
			IDebugDrawerInput& InDebugDrawerInput);
	private:
		SGameContext* BuiltGameContext;
		SRenderingContext* BuiltRenderingContext;
	};
}

namespace SS = SpelSylt;