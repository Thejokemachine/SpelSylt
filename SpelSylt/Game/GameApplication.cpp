#include "Game/GameApplication.h"

#include "Game/HookGame.h"
#include "Game/HookUIState.h"
#include <SpelSylt/UI/Base/UIState.h>

#include <SpelSylt/FileHandling/ConfigReader.h>

using namespace SpelSylt;

void CGameApplication::SetUpWindow()
{
	CConfigReader CfgReader;
	CfgReader.ReadConfigFile("HookGame.cfg");

	const unsigned int WindowW = CfgReader.GetAsUint("WinW");
	const unsigned int WindowH = CfgReader.GetAsUint("WinH");

	CApplication::SetWindowTitle("Game");
	CApplication::CreateWindow(WindowW, WindowH);
}

void CGameApplication::PushStartUpStates()
{
	CApplication::PushState(new HookGame());
	//CApplication::PushState(new UIState(1600, 900, "UI/Layouts/hookGame_layout.xml"));
}