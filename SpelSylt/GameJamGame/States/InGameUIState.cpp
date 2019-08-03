#include "InGameUIState.h"

#include <SpelSylt/UI/Label.h>
#include <SpelSylt/Contexts/GameContext.h>
#include <SpelSylt/Utility/Time/TimeGetter.h>
#include <SpelSylt/Messaging/MessageQueue.h>

#include "GameJamGame/Core/GameMessages.h"

tree::CInGameUIState::CInGameUIState(unsigned int aWidth, unsigned int aHeight) :
	UI::UIState(aWidth, aHeight, "UI/Layouts/ingame_layout.xml")
{
	UIState::SetStateFlags(StateFlags::UPDATE_BELOW | CState::DRAW_BELOW);
}

void tree::CInGameUIState::OnInit(SGameContext & InGameContext)
{
	myWaterPrompt = myLayout->GetLabel("water_prompt");

	InGameContext.MessageQueue.Subscribe<ShowWaterPrompt>([this](const auto& msg) {
		if (myWaterPrompt) {
			myWaterPrompt->SetVisible(true);
		}
	}, mySubs);
	InGameContext.MessageQueue.Subscribe<HideWaterPrompt>([this](const auto& msg) {
		if (myWaterPrompt) {
			myWaterPrompt->SetVisible(false);
		}
	}, mySubs);
	InGameContext.MessageQueue.Subscribe<AmmoMsg>([this](const auto& msg) {
		if (auto label = myLayout->GetLabel("ammo")) {
			label->SetText("AMMO: " + std::to_string(msg.Param));
		}
	}, mySubs);
}

void tree::CInGameUIState::OnUpdate(SGameContext & InGameContext)
{
	auto c = myWaterPrompt->GetTextColor();
	c.a = 255.f * (0.3f + 0.2f * sinf(5.f * InGameContext.Time.GetTotalTime()));
	myWaterPrompt->SetTextColor(c);
}

void tree::CInGameUIState::OnRender(sf::RenderTarget & InTarget)
{
}
