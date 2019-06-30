#pragma once

#include "DebugDrawer.h"

#include "Renderer.h"
#include "RenderingContext.h"
#include "RenderQueue.h"

#include "InputManager.h"
#include "Time.h"
#include "GameContext.h"

#include "StateStack.h"

#include <SFML/Graphics/RenderWindow.hpp>


class CApplication
{
public:
	CApplication();
	CApplication(const CApplication&) = delete;
	CApplication(CApplication&&) = delete;

	void Initialize();
	bool Run();
private:
	void CreateWindow();

	void PrepareForNewFrame();
	void PublishNewFrame();

	bool HandleEvents();

	CInputManager InputManager;
	CTime Time;

	CStateStack StateStack;

	sf::RenderWindow Window;
	
	CRenderer Renderer;
	CDebugDrawer DebugDrawer;

	CRenderQueue RenderQueue;

	//Contexts
	SGameContext GameContext;
	SRenderingContext RenderingContext;
};