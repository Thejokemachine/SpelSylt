#pragma once
#include "SpelSylt/State/State.h"
#include "SpelSylt/UI/Base/UILayout.h"
#include "SpelSylt/FileHandling/Banks/FontBank.h"
#include "SpelSylt/Messaging/Subscribing/MessageSubscriberList.h"
#include <SpelSylt/Messaging/Subscribing/Subscriptions.h>

namespace sf {
	class RenderTarget;
}

class UIState : public CState
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
private:

	CSubscriptions mySubs;
	float myWidth;
	float myHeight;

#ifdef _DEBUG
	bool myShouldReload = false;
	std::string myLayoutFile;
#endif
};