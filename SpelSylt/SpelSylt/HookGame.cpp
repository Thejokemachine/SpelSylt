#include "HookGame.h"
#include "SFML/Graphics/RenderWindow.hpp"

#include "CommonMath.h"
#include "InputManager.h"

#include <iostream>

HookGame::HookGame()
{
}

HookGame::~HookGame()
{
}

void HookGame::Init()
{
	myPlayerPos = sf::Vector2f(800.f, 900.f);
}

void HookGame::Update(float dt)
{
	sf::Vector2f hookPoint = sf::Vector2f(800.f, 450.f);
	myDrawer.DrawCircle(hookPoint, 2.f, true);
	if (myIsHooked)
		myDrawer.DrawLine(hookPoint, myPlayerPos);

	auto im = CInputManager::GetInstance();
	if (im.IsKeyDown(EKeyCode::Up))
	{
		if (!myIsHooked)
			myRopeLength = Math::Length(myPlayerPos - hookPoint);
		myIsHooked = true;

		std::cout << myRopeLength << std::endl;
	}
	else
	{
		myIsHooked = false;
	}

	myVelocity.y += 2500.f * dt;

	if (!myIsHooked)
	{
		if (myIsGrounded && im.IsKeyPressed(EKeyCode::Space))
			myVelocity.y = -1000.f;
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
		sf::Vector2f p = myPlayerPos + myVelocity * dt;
		if (Math::Length(p - hookPoint) > myRopeLength)
		{
			sf::Vector2f restrainedP = (hookPoint + myRopeLength * Math::GetNormalized(p - hookPoint));
			myVelocity = (restrainedP - myPlayerPos) / dt;
			myPlayerPos = restrainedP;
		}
		else
		{
			myPlayerPos += myVelocity * dt;
		}
	}

	myDrawer.DrawLine(myPlayerPos, myPlayerPos + myVelocity, sf::Color::Blue);

	myPlayerPos.y = Math::Min(myPlayerPos.y, 900.f);
	myIsGrounded = myPlayerPos.y == 900.f;
}

void HookGame::Render(sf::RenderWindow * aRenderWindow)
{
	sf::Vector2f playerOffset = myPlayerPos;
	playerOffset.y -= 50.f;
	myDrawer.DrawRectangle(playerOffset, 50.f, 100.f, true);

	aRenderWindow->draw(myDrawer);
	myDrawer.clear();
}
