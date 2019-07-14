#include "SpelSylt/SpelSyltPCH.h"
#include "SpelSylt/UI/Base/UIState.h"
#include "SpelSylt/Contexts/GameContext.h"
#include "SpelSylt/UI/Button.h"
#include "SpelSylt/Messaging/Messages/UIMessages.h"
#include "SpelSylt/Messaging/MessageQueue.h"

#ifdef _DEBUG
#include <SpelSylt/FileHandling/FileWatcher.h>
#endif

CFontBank UIState::FontBank;

UIState::UIState(unsigned int aWidth, unsigned int aHeight, const std::string& aLayoutXML) :
	CState(),
	myLayout(std::make_unique<UI::UILayout>((float)aWidth, (float)aHeight, FontBank, aLayoutXML))
{
	SetStateFlags(CState::DRAW_BELOW | CState::UPDATE_BELOW);

	myTexture.create(aWidth, aHeight);
	mySprite.setTexture(myTexture.getTexture());

#ifdef _DEBUG
	myLayoutFile = aLayoutXML;
	SS::CFileWatcher::AddFile(aLayoutXML.c_str(), [this, aWidth, aHeight](){
		myShouldReload = true;
	});
#endif
}

void UIState::Init(SGameContext& InGameContext, SRenderingContext& InRenderingContext)
{
	InGameContext.MessageQueue.Subscribe<SResizedWindowMessage>([this](const SResizedWindowMessage& msg) {
		myTexture.create(msg.Param, msg.ParamTwo);
		mySprite.setTexture(myTexture.getTexture(), true);
		myLayout->Resize(msg.Param, msg.ParamTwo);
	}, mySubs);

	OnInit(InGameContext, InRenderingContext);
}

void UIState::Update(SGameContext & InGameContext)
{
	myLayout->Update(&InGameContext.Input);

#ifdef _DEBUG
	if (myShouldReload)
	{
		myLayout = nullptr;
		myLayout = std::make_unique<UI::UILayout>((float)myTexture.getSize().x, (float)myTexture.getSize().y, FontBank, myLayoutFile);
		myShouldReload = false;
		LOG_VERBOSE(UI, "Reloaded UI");
	}
#endif

	OnUpdate(InGameContext);
}

void UIState::Render(SRenderingContext & InRenderingContext)
{
	myTexture.clear(sf::Color(0,0,0,0));

	myTexture.setView(sf::View(sf::FloatRect(0.f, 0.f, (float)myTexture.getSize().x, (float)myTexture.getSize().y)));
	myLayout->Render(myTexture);

	OnRender(myTexture);

	myTexture.display();
	mySprite.setPosition(InRenderingContext.Camera.getCenter() - 0.5f * sf::Vector2f((float)myTexture.getSize().x, (float)myTexture.getSize().y));

	InRenderingContext.RenderQueue.Enqueue(ERenderLayer::UI, SSpriteRenderCommand(mySprite));
}
