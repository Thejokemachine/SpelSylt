#include "GameState.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "DebugDrawer.h"

GameState::GameState()
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
}

void GameState::Render(sf::RenderWindow * aRenderWindow)
{
	aRenderWindow->draw(dd);
	dd.clear();
}
