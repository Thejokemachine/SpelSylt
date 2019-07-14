#pragma once
#include <SpelSylt/UI/Base/UIState.h>

#include "SimpleAnimation.h"

namespace AnimationEditor {

	class AnimationEditorState : public UIState
	{
	public:
		AnimationEditorState(unsigned width, unsigned int height, const std::string& aLayoutXML);
		virtual ~AnimationEditorState() = default;

		virtual void OnInit(SGameContext& InGameContext, SRenderingContext& InRenderingContext) override;
		virtual void OnUpdate(SGameContext& InGameContext) override;
		virtual void OnRender(sf::RenderTarget& target) override;

	private:

		bool isPlaying = false;
		SimpleAnimation animation;

	};
}