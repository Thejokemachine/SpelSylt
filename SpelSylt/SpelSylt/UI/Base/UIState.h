#pragma once
#include "SpelSylt/State/State.h"
#include "SpelSylt/UI/Base/UILayout.h"
#include "SpelSylt/Messaging/Subscribing/MessageSubscriberList.h"
#include <SpelSylt/Messaging/Subscribing/Subscriptions.h>

namespace sf {
	class RenderTarget;
}

namespace UI
{
	class UIState : public SpelSylt::CState
	{
	public:
		UIState(unsigned int aWidth, unsigned int aHeight, const std::string& aLayoutXML);
		~UIState() = default;

		virtual void Init(SGameContext& InGameContext) final override;
		virtual void Update(SGameContext& InGameContext) final override;
		virtual void Render(sf::RenderTarget& InTarget) final override;

	protected:
		virtual void OnInit(SGameContext& InGameContext) {}
		virtual void OnUpdate(SGameContext& InGameContext) {}
		virtual void OnRender(sf::RenderTarget& InTarget) {}

		std::unique_ptr<UI::UILayout> myLayout;
		CSubscriptions mySubs;

	private:
		float myWidth;
		float myHeight;

		std::string myLayoutFile;
#ifdef _DEBUG
		bool myShouldReload = false;
#endif
	};
}