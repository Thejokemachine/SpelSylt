#pragma once

namespace SpelSylt
{
	class ITimeGetter;
	class IInputEventGetter;
	class CAsyncLoader;
	class CSynchronousLoader;
	class CMessageQueue;
	class CAssetManager;
	class CAudioManager;

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
			SpelSylt::CAssetManager& InAssetManager,
			CAudioManager& InAudioManager
		)
			: Input(InInputEventGetter)
			, Time(InTimeGetter)
			, AsyncLoader(InAsyncLoader)
			, SynchronousLoader(InSynchronousLoader)
			, MessageQueue(InMessageQueue)
			, AssetManager(InAssetManager)
			, AudioManager(InAudioManager)
		{}

		IInputEventGetter& Input;
		ITimeGetter& Time;
		CAsyncLoader& AsyncLoader;
		CSynchronousLoader& SynchronousLoader;
		CMessageQueue& MessageQueue;
		SpelSylt::CAssetManager& AssetManager;
		CAudioManager& AudioManager;
	};
}

namespace SS = SpelSylt;