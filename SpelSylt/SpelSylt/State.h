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
	CState();
	virtual ~CState();

	void SetOwner(CStateStack* aOwner);

	virtual void Init() = 0;
	virtual void Update(SGameContext& InGameContext) = 0;
	virtual void Render(SRenderingContext& InRenderingContext) = 0;

protected:
	bool Pop();
	void PopAll();

	void Push(CState* aNewState);

private:
	CStateStack* myOwner;
};

