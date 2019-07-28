#include "LoadingState.h"
#include "HookGame.h"
#include <SpelSylt/Contexts/GameContext.h>
#include <SpelSylt/Utility/Time/Time.h>

LoadingState::LoadingState(unsigned width, unsigned height) : 
	UI::UIState(width, height, "UI/Layouts/loading_layout.xml")
{
}

void LoadingState::OnInit(SGameContext & InGameContext)
{
	myLoadingTimer.Init(CTimedEvent::EType::DoOnce, 5.f, [this](){
		CState::Pop();
	});

	myLoadingTimer.Start();
}

void LoadingState::OnUpdate(SGameContext & InGameContext)
{
	myLoadingTimer.Update(InGameContext.Time.GetDeltaTime());
}

void LoadingState::OnRender(sf::RenderTarget & InTarget)
{
}
