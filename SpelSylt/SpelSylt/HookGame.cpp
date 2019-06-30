#include "SpelSyltPCH.h"

/*
#include "HookGame.h"
#include "SFML/Graphics/RenderWindow.hpp"

#include "CommonMath.h"
#include "InputManager.h"

#include <iostream>

HookGame::HookGame() :
myUI(1600, 900)
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

	myCamera.setSize(1600, 900);
}

void HookGame::Update(float dt)
{
	sf::Vector2f pAnchor = myPlayerPos;
	pAnchor.y -= 100.f;

	if (!myIsHooked)
	{
		for (auto point : myHookPoints)
		{
			if (point.y <= pAnchor.y)
			{
				if (Math::Length(myHookPoint - pAnchor) > Math::Length(point - pAnchor))
					myHookPoint = point;
			}
		}
	}
	myDrawer.DrawCircle(myHookPoint, 5.f, true, sf::Color::Blue);

	auto im = CInputManager::GetInstance();
	if (im.IsKeyPressed(EKeyCode::Up))
	{
		if (!myIsHooked)
		{
			myRopeLength = Math::Length(myHookPoint - pAnchor);
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
		sf::Vector2f p = pAnchor + myVelocity * dt;
		if (Math::Length(p - myHookPoint) > myRopeLength)
		{
			sf::Vector2f restrainedP = (myHookPoint + myRopeLength * Math::GetNormalized(p - myHookPoint));
			myVelocity = (restrainedP - pAnchor) / dt;
			myPlayerPos = restrainedP;
			myPlayerPos.y += 100.f;
		}
		else
		{
			myPlayerPos += myVelocity * dt;
		}
		myDrawer.DrawLine(pAnchor, myHookPoint);
	}

	myDrawer.DrawLine(myPlayerPos, myPlayerPos + myVelocity, sf::Color::Blue);

	myPlayerPos.y = Math::Min(myPlayerPos.y, 900.f);
	myIsGrounded = myPlayerPos.y == 900.f;

	myCamera.setCenter(myCamera.getCenter().x, myPlayerPos.y - 300.f);

	myUI.Update(&im);
}

void HookGame::Render(sf::RenderWindow * aRenderWindow)
{

	for (auto hookPoint : myHookPoints)
	{
		myDrawer.DrawCircle(hookPoint, 2.f, true);
	}

	sf::Vector2f playerOffset = myPlayerPos;
	playerOffset.y -= 50.f;
	myDrawer.DrawRectangle(playerOffset, 50.f, 100.f, true);

	//aRenderWindow->setView(myCamera);
	aRenderWindow->draw(myDrawer);
	myDrawer.clear();

	myUI.Render(*aRenderWindow);
}
*/
