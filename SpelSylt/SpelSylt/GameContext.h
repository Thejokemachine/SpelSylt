#pragma once

class ITimeGetter;
class IInputEventGetter;
class IAsyncLoader;

struct SGameContext
{
public:
	SGameContext() = delete;
	SGameContext(
		IInputEventGetter& InInputEventGetter,
		ITimeGetter& InTimeGetter,
		IAsyncLoader& InAsyncLoader
	)
		: Input(InInputEventGetter)
		, Time(InTimeGetter)
		, Loader(InAsyncLoader)
	{}

	IInputEventGetter& Input;
	ITimeGetter& Time;
	IAsyncLoader& Loader;
};
