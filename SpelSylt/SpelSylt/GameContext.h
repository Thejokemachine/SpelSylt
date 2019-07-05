#pragma once

class ITimeGetter;
class IInputEventGetter;
class IAsyncLoader;
class ITextureProvider;

struct SGameContext
{
public:
	SGameContext() = delete;
	SGameContext(
		IInputEventGetter& InInputEventGetter,
		ITimeGetter& InTimeGetter,
		IAsyncLoader& InAsyncLoader,
		ITextureProvider& InTextureProvider
	)
		: Input(InInputEventGetter)
		, Time(InTimeGetter)
		, Loader(InAsyncLoader)
		, TextureProvider(InTextureProvider)
	{}

	IInputEventGetter& Input;
	ITimeGetter& Time;
	IAsyncLoader& Loader;
	ITextureProvider& TextureProvider;
};
