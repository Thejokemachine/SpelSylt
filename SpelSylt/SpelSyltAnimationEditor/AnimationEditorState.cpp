#include "AnimationEditorState.h"

#include <SpelSylt/UI/Base/UILayout.h>
#include <Spelsylt/UI/Button.h>
#include <SpelSylt/UI/Label.h>
#include <SpelSylt/Contexts/GameContext.h>
#include <SpelSylt/Contexts/RenderingContext.h>
#include <SpelSylt/Utility/Time/Time.h>

using namespace AnimationEditor;
using namespace UI;

AnimationEditorState::AnimationEditorState(unsigned width, unsigned int height, const std::string & aLayoutXML) :
	UIState(width, height, aLayoutXML)
{
	if (auto btn = myLayout->GetButton("play_btn")) {
		btn->SetCallback([this](Button& button) {
			isPlaying = !isPlaying;
		});
	}
	if (auto label = myLayout->GetLabel("clip_bg_text")) {
		label->SetText("Hej Sofia! :D");
	}
}

void AnimationEditorState::OnInit(SGameContext & InGameContext, SRenderingContext & InRenderingContext)
{
	animation.addFrame("UI/Images/TestSprite.png", 0.25f);
	animation.addFrame("UI/Images/gradient.png", 1.5f);
}

void AnimationEditorState::OnUpdate(SGameContext & InGameContext)
{
	if (isPlaying) {
		animation.tick(InGameContext.Time.GetDeltaTime());
	}
}

void AnimationEditorState::OnRender(sf::RenderTarget& target)
{
	target.draw(animation);
}
