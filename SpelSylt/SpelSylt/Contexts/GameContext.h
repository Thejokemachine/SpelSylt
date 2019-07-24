#pragma once

class ITimeGetter;
class IInputEventGetter;
class ILoader;
class CMessageQueue;

namespace SpelSylt
{
	class CAssetManager;
}

struct SGameContext
{
public:
	SGameContext() = delete;
	SGameContext(
		IInputEventGetter& InInputEventGetter,
		ITimeGetter& InTimeGetter,
		ILoader& InAsyncLoader,
		CMessageQueue& InMessageQueue,
		SpelSylt::CAssetManager& InAssetManager
	)
		: Input(InInputEventGetter)
		, Time(InTimeGetter)
		, Loader(InAsyncLoader)
		, MessageQueue(InMessageQueue)
		, AssetManager(InAssetManager)
	{}

	IInputEventGetter& Input;
	ITimeGetter& Time;
	ILoader& Loader;
	CMessageQueue& MessageQueue;
	SpelSylt::CAssetManager& AssetManager;
};
