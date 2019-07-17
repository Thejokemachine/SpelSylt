#include "Game/HookGame.h"
#include "SFML/Graphics/RenderWindow.hpp"

#include "SpelSylt/Math/CommonMath.h"
#include "SpelSylt/Utility/Input/InputManager.h"

#include <iostream>

#include "SpelSylt/FileHandling/Asset/Assets.h"

#include "SpelSylt/Contexts/GameContext.h"
#include "SpelSylt/Contexts/RenderingContext.h"
#include "SpelSylt/Messaging/MessageQueue.h"
#include "SpelSylt/FileHandling/Loading/AsyncLoaderInterface.h"
#include "SpelSylt/Utility/Time/TimeGetter.h"

#include "SpelSylt/Messaging/Messages/AudioMessages.h"

HookGame::HookGame()
	: myIsGrounded(true)
	, SetTexture(false)
{
}

HookGame::~HookGame()
{
}

void HookGame::Init(SGameContext& InGameContext)
{
	myPlayerPos = sf::Vector2f(800.f, 900.f);

	for (int i = 0; i < 100; ++i)
	{
		myHookPoints.emplace_back(sf::Vector2f(200.f + (float)(rand() % 1200), 500.f - i * 75.f));
	}

	InGameContext.MessageQueue.DispatchEvent<SMusicMessage>("HookGameOst", false);
}

void HookGame::Update(SGameContext& InGameContext)
{
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
			InGameContext.MessageQueue.DispatchEvent<SSoundMessage>("HookNoise");
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

	myCamera.setCenter(myCamera.getCenter().x, myPlayerPos.y);
}

void HookGame::Render(sf::RenderTarget& InTarget)
{
	myCamera.setSize((float)InTarget.getSize().x, (float)InTarget.getSize().y);

	myRenderQueue.Enqueue(ERenderLayer::Game, SSpriteRenderCommand(TestSprite));

	myDebugDrawer.DrawCircle(myHookPoint, 5.f, true, sf::Color::Blue);

	for (auto hookPoint : myHookPoints)
	{
		myDebugDrawer.DrawCircle(hookPoint, 2.f, true);
	}

	sf::Vector2f playerOffset = myPlayerPos;
	playerOffset.y -= 50.f;
	myDebugDrawer.DrawRectangle(playerOffset, 50.f, 100.f, true);

	if (myIsHooked)
	{
		myDebugDrawer.DrawLine(Anchor, myHookPoint);
	}


	myDebugDrawer.DrawLine(myPlayerPos, myPlayerPos + myVelocity, sf::Color::Blue);

	InTarget.setView(myCamera);

	myRenderer.RunRenderAllLayers(myRenderQueue, InTarget);
	InTarget.draw(myDebugDrawer);

	myDebugDrawer.clear();
}
