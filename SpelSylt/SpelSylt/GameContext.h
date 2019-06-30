#pragma once

class ITimeGetter;
class IInputEventGetter;

struct SGameContext
{
public:
	SGameContext() = delete;
	SGameContext(
		IInputEventGetter& InInputEventGetter,
		ITimeGetter& InTimeGetter
	)
		: Input(InInputEventGetter)
		, Time(InTimeGetter)
	{}

	IInputEventGetter& Input;
	ITimeGetter& Time;
};
