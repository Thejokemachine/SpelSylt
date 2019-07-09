#include "Game/GameApplication.h"

#include <SpelSylt/UI/Base/UIState.h>

void CGameApplication::SetUpWindow()
{
	CApplication::SetWindowTitle("Game");
	CApplication::CreateWindow(800, 600);
}

void CGameApplication::PushStartUpStates()
{
	CApplication::PushState(new UIState(800, 600, "UI/Layouts/layout.xml"));
}