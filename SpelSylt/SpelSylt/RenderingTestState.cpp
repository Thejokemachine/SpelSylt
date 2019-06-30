#include "SpelSyltPCH.h"

#include "RenderingTestState.h"

#include "RenderCommand.h"
#include "RenderingContext.h"

#include "InputManager.h"

//------------------------------------------------------------------

CRenderingTestState::CRenderingTestState()
{
}

//------------------------------------------------------------------

void CRenderingTestState::Init()
{
	TestSpriteTexture.loadFromFile("Graphics/Sprites/TestSprite.png");
	TestSprite.setTexture(TestSpriteTexture);
}

//------------------------------------------------------------------

void CRenderingTestState::Update(float InDT)
{
	CInputManager& InputManager = CInputManager::GetInstance();
	
	const float Speed = 30.f;
	sf::Vector2f Direction;

	if (InputManager.IsKeyDown(EKeyCode::A))
	{
		Direction.x -= 1;
	}
	if (InputManager.IsKeyDown(EKeyCode::D))
	{
		Direction.x += 1;
	}

	const sf::Vector2f OldPos = TestSprite.getPosition();
	const sf::Vector2f NewPos = OldPos + (Direction * Speed * InDT);
	TestSprite.setPosition(NewPos);
}

//------------------------------------------------------------------

void CRenderingTestState::Render(SRenderingContext& InRenderingContext)
{
	InRenderingContext.DebugDrawer.DrawCircle(TestSprite.getPosition(), 64.f, false);

	//SSpriteRenderCommand Command(TestSprite);
	//InRenderingContext.RenderQueue.Enqueue(ERenderLayer::Game, Command);
}

//------------------------------------------------------------------