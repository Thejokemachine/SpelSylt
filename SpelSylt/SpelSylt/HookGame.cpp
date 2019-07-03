#include "SpelSyltPCH.h"

#include "HookGame.h"
#include "SFML/Graphics/RenderWindow.hpp"

#include "CommonMath.h"
#include "InputManager.h"

#include <iostream>

#include "Assets.h"

HookGame::HookGame() 
	: myIsGrounded(true)
	, SetTexture(false)
{
}

HookGame::~HookGame()
{
}

void HookGame::Init()
{
	myPlayerPos = sf::Vector2f(800.f, 900.f);

	for (int i = 0; i < 100; ++i)
	{
		myHookPoints.emplace_back(sf::Vector2f(200.f + (float)(rand() % 1400), 500.f - i * 75.f));
	}
}

void HookGame::Update(SGameContext& InGameContext)
{
	if (TestTexture.GetLoadStatus() != ELoadRequestStatus::Done && InGameContext.Time.GetTotalTime() > 10.f)
	{
		InGameContext.Loader.LoadAsync("Graphics/Sprites/BigTest.png", TestTexture);
	}
	if (!SetTexture && TestTexture.GetLoadStatus() == ELoadRequestStatus::Done)
	{
		TestSprite.setTexture(TestTexture);
		SetTexture = true;
	}


	const float dt = InGameContext.Time.GetDeltaTime();

	Anchor = myPlayerPos;
	Anchor.y -= 100.f;

	if (!myIsHooked)
	{
		for (auto point : myHookPoints)
		{
			if (point.y <= Anchor.y)
			{
				if (Math::Length(myHookPoint - Anchor) > Math::Length(point - Anchor))
					myHookPoint = point;
			}
		}
	}

	auto& im = InGameContext.Input;
	if (im.IsKeyPressed(EKeyCode::Up))
	{
		if (!myIsHooked)
		{
			myRopeLength = Math::Length(myHookPoint - Anchor);
		}
		myIsHooked = !myIsHooked;
	}

	myVelocity.y += 2500.f * dt;

	if ((myIsGrounded || myIsHooked) && im.IsKeyPressed(EKeyCode::Space))
	{
		myVelocity.y = -1000.f;
		myIsHooked = false;
	}

	if (!myIsHooked)
	{
		if (im.IsKeyDown(EKeyCode::Left))
			myVelocity.x = -200.f;
		if (im.IsKeyDown(EKeyCode::Right))
			myVelocity.x = 200.f;
		if (myIsGrounded && !im.IsKeyDown(EKeyCode::Left) && !im.IsKeyDown(EKeyCode::Right))
			myVelocity.x = 0.f;

		myPlayerPos += myVelocity * dt;
	}
	else
	{
		sf::Vector2f p = Anchor + myVelocity * dt;
		if (Math::Length(p - myHookPoint) > myRopeLength)
		{
			sf::Vector2f restrainedP = (myHookPoint + myRopeLength * Math::GetNormalized(p - myHookPoint));
			myVelocity = (restrainedP - Anchor) / dt;
			myPlayerPos = restrainedP;
			myPlayerPos.y += 100.f;
		}
		else
		{
			myPlayerPos += myVelocity * dt;
		}
	}

	myPlayerPos.y = Math::Min(myPlayerPos.y, 900.f);
	myIsGrounded = myPlayerPos.y == 900.f;
}

void HookGame::Render(SRenderingContext& InContext)
{

	InContext.Camera.setCenter(InContext.Camera.getCenter().x, myPlayerPos.y - 300.f);

	TestSprite.setPosition(InContext.Camera.getCenter());
	InContext.RenderQueue.Enqueue(ERenderLayer::Game, SSpriteRenderCommand(TestSprite));

	InContext.DebugDrawer.DrawCircle(myHookPoint, 5.f, true, sf::Color::Blue);

	for (auto hookPoint : myHookPoints)
	{
		InContext.DebugDrawer.DrawCircle(hookPoint, 2.f, true);
	}

	sf::Vector2f playerOffset = myPlayerPos;
	playerOffset.y -= 50.f;
	InContext.DebugDrawer.DrawRectangle(playerOffset, 50.f, 100.f, true);

	if (myIsHooked)
	{
		InContext.DebugDrawer.DrawLine(Anchor, myHookPoint);
	}
	

	InContext.DebugDrawer.DrawLine(myPlayerPos, myPlayerPos + myVelocity, sf::Color::Blue);
}
