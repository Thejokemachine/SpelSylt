#pragma once
#include "SpelSylt/Contexts/GameContext.h"
#include "SpelSylt/Contexts/RenderingContext.h"

namespace SpelSylt
{
	class ITimeGetter;
	class IInputEventGetter;
	class CAsyncLoader;
	class CSynchronousLoader;
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
			CAsyncLoader& InAsyncLoader,
			CSynchronousLoader& InSynchronousLoader,
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