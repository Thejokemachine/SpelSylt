#pragma once
#include "SpelSylt/State/State.h"
#include "SpelSylt/UI/Base/UILayout.h"
#include "SpelSylt/FileHandling/Banks/FontBank.h"
#include "SpelSylt/Messaging/Subscribing/MessageSubscriberList.h"

#ifdef _DEBUG
#include <SpelSylt/FileHandling/FileWatcher.h>
#endif

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RenderTexture.hpp"

class UIState : public CState
{
public:
	UIState(unsigned int aWidth, unsigned int aHeight, const std::string& aLayoutXML);
	~UIState() = default;

	virtual void Init(SGameContext& InGameContext, SRenderingContext& InRenderingContext) override;
	virtual void Update(SGameContext& InGameContext) override;
	virtual void Render(SRenderingContext& InRenderingContext) override;
private:
	
	sf::Sprite mySprite;
	sf::RenderTexture myTexture;

	CSubscriptions mySubs;

	std::unique_ptr<UI::UILayout> myLayout;
	static CFontBank FontBank;

#ifdef _DEBUG
	CFileWatcher myFileWatcher;
	bool myShouldReload = false;
	std::string myLayoutFile;
#endif
};