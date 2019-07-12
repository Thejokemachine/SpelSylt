#pragma once
#include <vector>

namespace sf
{
	class Window;
}

class CState;
struct SGameContext;
struct SRenderingContext;


class CStateStack
{
public:
	CStateStack(sf::Window& aWindow);
	~CStateStack();

	void Update(SGameContext& InGameContext);
	void Render(SRenderingContext& InRenderingContext);

	const sf::Window& GetWindow() const { return myWindow; }

	void Push(CState* aNewState, SGameContext& InGameContext, SRenderingContext& InRenderingContext);
	bool Pop();
	void PopAll();

	short Size();

private:
	std::vector<CState*> myStates;
	sf::Window& myWindow;
};

