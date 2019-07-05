#include "SpelSyltPCH.h"
#include "UIState.h"

UIState::UIState(unsigned int aWidth, unsigned int aHeight) :
	CState(),
	myLayout((float)aWidth, (float)aHeight)
{
	SetStateFlags(CState::DRAW_BELOW | CState::UPDATE_BELOW);

	myTexture.create(aWidth, aHeight);
	mySprite.setTexture(myTexture.getTexture());
	mySprite.setOrigin(aWidth * 0.5f, aHeight * 0.5f);
}

void UIState::Init(SGameContext& InGameContext, SRenderingContext& InRenderingContext)
{
}

void UIState::Update(SGameContext & InGameContext)
{
}

void UIState::Render(SRenderingContext & InRenderingContext)
{
	myTexture.clear(sf::Color(0,0,0,0));

	myLayout.Render(myTexture);

	myTexture.display();
	mySprite.setPosition(InRenderingContext.Camera.getCenter());

	InRenderingContext.RenderQueue.Enqueue(ERenderLayer::UI, SSpriteRenderCommand(mySprite));
}
