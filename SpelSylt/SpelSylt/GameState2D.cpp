#include "SpelSylt/SpelSyltPCH.h"
#include "GameState2D.h"

#include <SFML/Graphics/RenderTarget.hpp>

using namespace SpelSylt;

GameState2D::GameState2D()
{
}

GameState2D::~GameState2D()
{
}

void GameState2D::Init(SGameContext & InGameContext)
{
	OnInit(InGameContext);
}

void GameState2D::Update(SGameContext & InGameContext)
{

	OnUpdate(InGameContext);
}

void GameState2D::Render(sf::RenderTarget & InTarget)
{
	myCamera.setSize((float)InTarget.getSize().x, (float)InTarget.getSize().y);
	InTarget.setView(myCamera);

	OnRender(myRenderQueue);

	myRenderer.RunRenderAllLayers(myRenderQueue, InTarget);
	myRenderQueue.Clear();

	InTarget.draw(myDebugDrawer);
	myDebugDrawer.clear();
}
