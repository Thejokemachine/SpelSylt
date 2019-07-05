#pragma once

namespace sf
{
	class RenderWindow;
}

class CStateStack;
struct SGameContext;
struct SRenderingContext;

class CState
{
public:

	enum StateFlags : int {
		NONE = 0,
		UPDATE_BELOW = 1,
		DRAW_BELOW = 2,
	};

	CState();
	virtual ~CState();

	void SetOwner(CStateStack* aOwner);
	void SetStateFlags(StateFlags aStateFlags);
	void SetStateFlags(int aStateFlags);

	StateFlags GetStateFlags() const { return myStateFlags; }

	virtual void Init(SGameContext& InGameContext, SRenderingContext& InRenderingContext) = 0;
	virtual void Update(SGameContext& InGameContext) = 0;
	virtual void Render(SRenderingContext& InRenderingContext) = 0;

protected:
	bool Pop();
	void PopAll();

	void Push(CState* aNewState);

private:
	CStateStack* myOwner;
	StateFlags myStateFlags;
};

