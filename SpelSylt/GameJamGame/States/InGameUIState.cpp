#include "InGameUIState.h"

tree::CInGameUIState::CInGameUIState(unsigned int aWidth, unsigned int aHeight) :
	UI::UIState(aWidth, aHeight, "UI/Layouts/ingame_layout.xml")
{
}

void tree::CInGameUIState::OnInit(SGameContext & InGameContext)
{
}

void tree::CInGameUIState::OnUpdate(SGameContext & InGameContext)
{
}

void tree::CInGameUIState::OnRender(sf::RenderTarget & InTarget)
{
}
