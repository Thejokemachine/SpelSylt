#include "Game/GameApplication.h"

#include "Game/HookGame.h"
#include "Game/HookUIState.h"
#include <SpelSylt/UI/Base/UIState.h>

void CGameApplication::SetUpWindow()
{
	CApplication::SetWindowTitle("Game");
	CApplication::CreateWindow(1600, 900);
}

void CGameApplication::PushStartUpStates()
{
	CApplication::PushState(new HookGame());
	CApplication::PushState(new UIState(1600, 900, "UI/Layouts/hookGame_layout.xml"));
}