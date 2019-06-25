#include "GameState.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "DebugDrawer.h"
#include "InputManager.h"

GameState::GameState() : 
myAudioManager("Audio/")
{
}

static DebugDrawer dd;

GameState::~GameState()
{
}

void GameState::Init()
{
}

void GameState::Update(float dt)
{
	dd.DrawLine(sf::Vector2f(0, 0), sf::Vector2f(1600, 900));
	dd.DrawRectangle(sf::Vector2f(800, 450), 600, 400);
	dd.DrawCircle(sf::Vector2f(800, 450), 100);
	dd.DrawText("Hello World", sf::Vector2f(25, 25));

	if (CInputManager::GetInstance().IsKeyPressed(EKeyCode::C))
		myAudioManager.PlaySound("shovel");

	myAudioManager.Update();
}

void GameState::Render(sf::RenderWindow * aRenderWindow)
{
	aRenderWindow->draw(dd);
	dd.clear();
}
