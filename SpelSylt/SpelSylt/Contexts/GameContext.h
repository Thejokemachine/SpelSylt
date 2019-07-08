#pragma once

class ITimeGetter;
class IInputEventGetter;
class IAsyncLoader;
class ITextureProvider;
class CMessageQueue;

struct SGameContext
{
public:
	SGameContext() = delete;
	SGameContext(
		IInputEventGetter& InInputEventGetter,
		ITimeGetter& InTimeGetter,
		IAsyncLoader& InAsyncLoader,
		ITextureProvider& InTextureProvider,
		CMessageQueue& InMessageQueue
	)
		: Input(InInputEventGetter)
		, Time(InTimeGetter)
		, Loader(InAsyncLoader)
		, TextureProvider(InTextureProvider)
		, MessageQueue(InMessageQueue)
	{}

	IInputEventGetter& Input;
	ITimeGetter& Time;
	IAsyncLoader& Loader;
	ITextureProvider& TextureProvider;
	CMessageQueue& MessageQueue;
};
