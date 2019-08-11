#pragma once
#include <SpelSylt/GameState2D.h>

namespace testproj
{
	class CTestProjectState
		: public SS::GameState2D
	{
	private:
		virtual void OnInit(SS::SGameContext& InGameContext) override;
		virtual void OnUpdate(SS::SGameContext& InGameContext) override;
		virtual void OnRender(SS::CRenderQueue& InRenderQueue) override;
	};
}