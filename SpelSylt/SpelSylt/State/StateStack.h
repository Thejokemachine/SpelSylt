#pragma once
#include <vector>

namespace sf
{
	class RenderWindow;
}

class CState;
struct SGameContext;
struct SRenderingContext;


class CStateStack
{
public:
	CStateStack();
	~CStateStack();

	void Update(SGameContext& InGameContext);
	void Render(SRenderingContext& InRenderingContext);

	void Push(CState* aNewState, SGameContext& InGameContext, SRenderingContext& InRenderingContext);
	bool Pop();
	void PopAll();

	short Size();

private:
	std::vector<CState*> myStates;
};

