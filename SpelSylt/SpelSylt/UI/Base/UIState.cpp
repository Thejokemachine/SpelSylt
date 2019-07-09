#include "SpelSylt/SpelSyltPCH.h"
#include "SpelSylt/UI/Base/UIState.h"
#include "SpelSylt/Contexts/GameContext.h"
#include "SpelSylt/UI/Button.h"
#include "SpelSylt/Messaging/Messages/UIMessages.h"
#include "SpelSylt/Messaging/MessageQueue.h"

CFontBank UIState::FontBank;

UIState::UIState(unsigned int aWidth, unsigned int aHeight) :
	CState(),
	myLayout((float)aWidth, (float)aHeight, FontBank)
{
	SetStateFlags(CState::DRAW_BELOW | CState::UPDATE_BELOW);

	myTexture.create(aWidth, aHeight);
	mySprite.setTexture(myTexture.getTexture());
	mySprite.setOrigin(aWidth * 0.5f, aHeight * 0.5f);
}

void UIState::Init(SGameContext& InGameContext, SRenderingContext& InRenderingContext)
{
	InGameContext.MessageQueue.Subscribe<SResizedWindowMessage>([this](const SResizedWindowMessage& msg) {
		myLayout.Resize(msg.Param, msg.ParamTwo);
	}, mySubs);
}

void UIState::Update(SGameContext & InGameContext)
{
	myLayout.Update(&InGameContext.Input);
}

void UIState::Render(SRenderingContext & InRenderingContext)
{
	myTexture.clear(sf::Color(0,0,0,0));

	myLayout.Render(myTexture);

	myTexture.display();
	mySprite.setPosition(InRenderingContext.Camera.getCenter());

	InRenderingContext.RenderQueue.Enqueue(ERenderLayer::UI, SSpriteRenderCommand(mySprite));

}
