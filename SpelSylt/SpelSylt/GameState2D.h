#pragma once
#include "SpelSylt/State/State.h"

#include "SpelSylt/Rendering/Renderer.h"
#include "SpelSylt/Rendering/RenderQueue.h"
#include "SpelSylt/Debugging/Rendering/DebugDrawer.h"

#include <memory>

#include <SFML/Graphics/View.hpp>

namespace SpelSylt
{
	class GameState2D : public CState
	{
	public:
		GameState2D();
		virtual ~GameState2D();

		virtual void Init(SGameContext& InGameContext) final override;
		virtual void Update(SGameContext& InGameContext) final override;
		virtual void Render(sf::RenderTarget& InTarget) final override;

		virtual void OnInit(SGameContext& InGameContext) {};
		virtual void OnUpdate(SGameContext& InGameContext) {};
		virtual void OnRender(CRenderQueue& InRenderQueue) {};

	protected:

		sf::View& GetCamera() { return myCamera; };

		CDebugDrawer myDebugDrawer;

	private:

		sf::View myCamera;

		std::unique_ptr<CRenderer> myRenderer;
		CRenderQueue myRenderQueue;
	};
}