#pragma once
#include <vector>

namespace sf
{
	class RenderWindow;
}

class CState;

class CStateStack
{
public:
	CStateStack();
	~CStateStack();

	void Update(float dt);
	void Render(sf::RenderWindow* aRenderWindow);

	void Push(CState* aNewState);
	bool Pop();
	void PopAll();

	short Size();

private:

	std::vector<CState*> myStates;
	short myCurrentStateIndex;
};

