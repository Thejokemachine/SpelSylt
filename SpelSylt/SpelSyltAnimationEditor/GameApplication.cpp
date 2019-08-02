#include "Game/GameApplication.h"

#include "AnimationEditorState.h"

using namespace AnimationEditor;
using namespace SpelSylt;

void CGameApplication::SetUpWindow()
{
	CApplication::SetWindowTitle("Game");
	CApplication::CreateWindow(800, 600);
}

void CGameApplication::PushStartUpStates()
{
	CApplication::PushState(std::make_shared<AnimationEditorState>(800, 600, "UI/Layouts/layout.xml"));
}