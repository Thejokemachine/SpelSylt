#include "GameJamGame/Core/GameApplication.h"

#include "GameJamGame/States/TreeGameState.h"

//------------------------------------------------------------------

using namespace tree;

//------------------------------------------------------------------

void CGameApplication::SetUpWindow()
{
	CApplication::SetWindowTitle("Game");
	CApplication::CreateWindow(1600, 900);
}

//------------------------------------------------------------------

void CGameApplication::PushStartUpStates()
{
	CApplication::PushState(std::make_shared<CTreeGameState>());
}

//------------------------------------------------------------------