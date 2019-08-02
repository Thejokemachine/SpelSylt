#include "GameJamGame/Core/GameApplication.h"

#include "GameJamGame/States/TreeGameState.h"
#include "GameJamGame/States/InGameUIState.h"

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
	CApplication::PushState(std::make_shared<CInGameUIState>(1600, 900));
}

//------------------------------------------------------------------