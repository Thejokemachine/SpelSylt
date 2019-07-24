#pragma once

namespace SpelSylt
{
	class ITimeGetter;
	class IInputEventGetter;
	class CAsyncLoader;
	class CSynchronousLoader;
	class CMessageQueue;
	class CAssetManager;

	struct SGameContext
	{
	public:
		SGameContext() = delete;
		SGameContext(
			IInputEventGetter& InInputEventGetter,
			ITimeGetter& InTimeGetter,
			CAsyncLoader& InAsyncLoader,
			CSynchronousLoader& InSynchronousLoader,
			CMessageQueue& InMessageQueue,
			SpelSylt::CAssetManager& InAssetManager
		)
			: Input(InInputEventGetter)
			, Time(InTimeGetter)
			, AsyncLoader(InAsyncLoader)
			, SynchronousLoader(InSynchronousLoader)
			, MessageQueue(InMessageQueue)
			, AssetManager(InAssetManager)
		{}

		IInputEventGetter& Input;
		ITimeGetter& Time;
		CAsyncLoader& AsyncLoader;
		CSynchronousLoader& SynchronousLoader;
		CMessageQueue& MessageQueue;
		SpelSylt::CAssetManager& AssetManager;
	};
}

namespace SS = SpelSylt;