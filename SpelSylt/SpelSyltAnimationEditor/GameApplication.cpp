#include "Game/GameApplication.h"

#include "AnimationEditorState.h"

using namespace AnimationEditor;

void CGameApplication::SetUpWindow()
{
	CApplication::SetWindowTitle("Game");
	CApplication::CreateWindow(800, 600);
}

void CGameApplication::PushStartUpStates()
{
	CApplication::PushState(new AnimationEditorState(800, 600, "UI/Layouts/layout.xml"));
}