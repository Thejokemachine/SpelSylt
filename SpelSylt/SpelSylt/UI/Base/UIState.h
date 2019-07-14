#pragma once
#include "SpelSylt/State/State.h"
#include "SpelSylt/UI/Base/UILayout.h"
#include "SpelSylt/FileHandling/Banks/FontBank.h"
#include "SpelSylt/Messaging/Subscribing/MessageSubscriberList.h"
#include <SpelSylt/Messaging/Subscribing/Subscriptions.h>

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RenderTexture.hpp"

class UIState : public CState
{
public:
	UIState(unsigned int aWidth, unsigned int aHeight, const std::string& aLayoutXML);
	~UIState() = default;

	virtual void Init(SGameContext& InGameContext, SRenderingContext& InRenderingContext) final override;
	virtual void Update(SGameContext& InGameContext) final override;
	virtual void Render(SRenderingContext& InRenderingContext) final override;

protected:
	virtual void OnInit(SGameContext& InGameContext, SRenderingContext& InRenderingContext) {}
	virtual void OnUpdate(SGameContext& InGameContext) {}
	virtual void OnRender(sf::RenderTarget& target) {}

	std::unique_ptr<UI::UILayout> myLayout;
private:
	
	sf::Sprite mySprite;
	sf::RenderTexture myTexture;

	CSubscriptions mySubs;

	static CFontBank FontBank;

#ifdef _DEBUG
	bool myShouldReload = false;
	std::string myLayoutFile;
#endif
};