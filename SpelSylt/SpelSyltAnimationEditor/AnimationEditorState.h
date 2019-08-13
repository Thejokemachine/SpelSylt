#pragma once
#include <SpelSylt/UI/Base/UIState.h>
#include <SpelSylt/Messaging/Subscribing/Subscriptions.h>
#include <SpelSylt/Messaging/MessageQueue.h>

#include "SimpleAnimation.h"

namespace UI {
	class Panel;
	class List;
	class Slider;
}

namespace AnimationEditor {

	class AnimationEditorState : public UI::UIState
	{
	public:
		AnimationEditorState(unsigned width, unsigned int height, const std::string& aLayoutXML);
		virtual ~AnimationEditorState() = default;

		virtual void OnInit(SGameContext& InGameContext) override;
		virtual void OnUpdate(SGameContext& InGameContext) override;
		virtual void OnRender(sf::RenderTarget& target) override;

	private:

		std::string openFileDialog();

		bool isPlaying = false;
		SimpleAnimation animation;

		UI::Panel* animCenter = nullptr;
		UI::List* frameList = nullptr;
		UI::Slider* slider = nullptr;

		CSubscriptions mySubs;
	};
}